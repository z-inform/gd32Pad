#include "gd32f10x_libopt.h"
#include "gd32f10x_rcu.c"
#include "gd32f10x_gpio.c"
#include "gd32f10x_misc.c"
#include "gd32f10x_timer.c"

#include "include/utime.h"
#include "include/ubutton.h"
extern uint32_t sys_tick;

void adc_uinit();

int main(void){
    volatile char command_flag = 0;
    uint32_t command_timeout = 0;
    uint32_t buttons_status = 0;
    volatile uint32_t cur_time = sys_tick;
    clock_uinit();
    gpio_uinit();
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_bit_set(GPIOC, GPIO_PIN_10);
    //blink_timer_uinit(500);

    volatile uint32_t counter = 0;
    while(1){
        cur_time = sys_tick;
        get_buttons(&buttons_status);
        if( ((buttons_status << 20 >> 28) == 0) && (time_delay(command_timeout, cur_time) > 500) ){
            counter += 1;
            command_timeout = cur_time;
            command_flag = !command_flag;
        }
        if( command_flag ) gpio_bit_reset(GPIOC, GPIO_PIN_10);
        else gpio_bit_set(GPIOC, GPIO_PIN_10);

    }
}



void adc_uinit(){
}


