#include "gd32f10x_libopt.h"

#include "include/utime.h"
#include "include/ubutton.h"
#include "include/uadc.h"

extern uint32_t sys_tick;

uint32_t interrupt = 0;

int main(void){
    /*
    volatile char command_flag = 0;
    uint32_t command_timeout = 0;
    uint32_t buttons_status = 0;
    volatile uint32_t cur_time = sys_tick;
    */
    uint8_t adc_array[4] = {};
    clock_uinit();
    gpio_uinit();
    gpio_bit_set(GPIOC, GPIO_PIN_10);
    adc_uinit();
    adc_dma_uinit(adc_array);
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);

    while(1){

        /*
        get_buttons(&buttons_status);
        if( ((buttons_status << 20 >> 28) == 0) && (time_delay(command_timeout, cur_time) > 500) ){
            command_timeout = cur_time;
            command_flag = !command_flag;
        }
        if( command_flag ) gpio_bit_reset(GPIOC, GPIO_PIN_10);
        else gpio_bit_set(GPIOC, GPIO_PIN_10);
        */
    }
}
