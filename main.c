#include "gd32f10x_libopt.h"
#include "gd32f10x_gpio.h"
#include "string.h"

#include "include/utime.h"
#include "include/ubutton.h"
#include "include/uadc.h"
#include "include/uprotocol.h"
#include "include/circ_buffer.h"

extern uint32_t sys_tick;
extern circ_buffer uart_read;
volatile char connected_state = 0;
volatile char error_state = 0;

uint32_t interrupt = 0;

int main(void){
    char* connected_string = "Connected";
    char* disconnect_string = "Disconnect";
    char* bat_string = "Batt\n";

    uint32_t command_timeout = 0;
    char command_mode = 0;


    struct parcel_struct{
        uint16_t adc_array[4];
        uint32_t buttons_status;
        uint32_t supp_data;
    } parcel;
    parcel.buttons_status = 0;

    clock_uinit();
    gpio_uinit();
    gpio_bit_reset(GPIOC, GPIO_PIN_10);
    gpio_bit_set(GPIOB, GPIO_PIN_13);
    adc_uinit();
    adc_dma_uinit(parcel.adc_array);
    uart_uinit();
    uart_dma_uinit();

    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);

    while(1){
        get_buttons(&parcel.buttons_status);

        if( !error_state ){
            adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);


            if( circmp(connected_string, &uart_read) == 0 ){
                connected_state = 1;
                dma_channel_enable(DMA0, DMA_CH0);
                gpio_bit_set(GPIOC, GPIO_PIN_10);
            }

            if( circmp("ERROR", &uart_read) == 0){
                error_state = 1;
                connected_state = 0;
                blink_timer_uinit(200);
                dma_channel_disable(DMA0, DMA_CH0);
            }

            if( connected_state ){



                if( circmp(disconnect_string, &uart_read) == 0 ){
                    connected_state = 0;
                    dma_channel_disable(DMA0, DMA_CH0);
                    gpio_bit_reset(GPIOC, GPIO_PIN_10);
                    //gpio_bit_reset(GPIOB, GPIO_PIN_13); //maybe change to reset pin later (HW not done yet)
                    //gpio_bit_set(GPIOB, GPIO_PIN_13);
                }

                if( circmp(bat_string, &uart_read) == 0 ){
                    //battery voltage from ADC
                }


                //uart_com_send((char*) &parcel, sizeof(parcel) * 4);
                uart_com_send(bat_string, 5);

            }
        }

        //check for command mode key combination
        if( ((parcel.buttons_status << 20 >> 28) == 0) &&
            (time_delay(command_timeout, sys_tick) > 500) ){
            command_timeout = sys_tick;
            command_mode = !command_mode;
        }

        //handle command mode keystrokes
        if( command_mode ){
            if( (parcel.buttons_status << 20 >> 30) == 0 ){
                error_state = 0;
                //dma_channel_enable(DMA0, DMA_CH0);
                gpio_bit_reset(GPIOC, GPIO_PIN_10);
                timer_disable(TIMER2);
            }
        }

    }
}










