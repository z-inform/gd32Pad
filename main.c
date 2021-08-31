#include "gd32f10x_libopt.h"

#include "include/utime.h"
#include "include/ubutton.h"
extern uint32_t sys_tick;

uint32_t interrupt = 0;

int main(void){
    volatile char command_flag = 0;
    uint32_t command_timeout = 0;
    uint32_t buttons_status = 0;
    volatile uint32_t cur_time = sys_tick;
    clock_uinit();
    gpio_uinit();
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_bit_set(GPIOC, GPIO_PIN_10);
    blink_timer_uinit(1000);

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
