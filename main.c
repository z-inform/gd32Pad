#include "gd32f10x_libopt.h"
#include "gd32f10x_gpio.h"
#include "string.h"

#include "include/utime.h"
#include "include/ubutton.h"
#include "include/uadc.h"
#include "include/uprotocol.h"

extern uint32_t sys_tick;
volatile char uart_read[40] = {0};
volatile char connected_state = 0;

uint32_t interrupt = 0;

int main(void){
    char* connected_string = "Connected\r\n";
    char* disconnect_string = "Disconnect\r\n";
    char* bat_string = "Battery\r\n";
    char string = 0xA;


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

        if( strcmp(uart_read, connected_string) == 0 ){
            connected_state = 1;
            dma_channel_enable(DMA0, DMA_CH0);
            gpio_bit_set(GPIOC, GPIO_PIN_10);
            gpio_bit_set(GPIOB, GPIO_PIN_13);
            memset((void*) uart_read, 0, sizeof(uart_read));
        }

        if( connected_state ){


            get_buttons(&parcel.buttons_status);

            if( strcmp(uart_read, disconnect_string) == 0 ){
                connected_state = 0;
                dma_channel_disable(DMA0, DMA_CH0);
                gpio_bit_reset(GPIOC, GPIO_PIN_10);
                //gpio_bit_reset(GPIOB, GPIO_PIN_13); //maybe change to reset pin later (HW not done yet)
                //gpio_bit_set(GPIOB, GPIO_PIN_13);
                memset((void*) uart_read, 0, sizeof(uart_read));
            }

            if( strcmp(uart_read, bat_string) == 9 ){
                memset((void*) uart_read, 0, sizeof(uart_read));
                //battery voltage from ADC
            }


            uart_com_send((char*) &parcel, sizeof(parcel) * 4);

        }
    }
}










