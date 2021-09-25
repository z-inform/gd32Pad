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

uint32_t interrupt = 0;

int main(void){
    char* connected_string = "Connected";
    char* disconnect_string = "Disconnect";
    char* bat_string = "Battery";


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
        adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);


        if( circmp(connected_string, &uart_read) == 0 ){
            connected_state = 1;
            dma_channel_enable(DMA0, DMA_CH0);
            gpio_bit_set(GPIOC, GPIO_PIN_10);
            gpio_bit_set(GPIOB, GPIO_PIN_13);
        }

        if( connected_state ){


            get_buttons(&parcel.buttons_status);

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


            uart_com_send((char*) &parcel, sizeof(parcel) * 4);

        }
    }
}










