#include "gd32f10x_gpio.h"

#include "../include/ubutton.h"
#include "../include/utime.h"
extern uint32_t sys_tick;

int get_buttons(uint32_t* but_status){
    static uint32_t jitter_delay_start[18] = {[0 ... 17] = 0};
    update_button(but_status, jitter_delay_start + 0, 0, GPIOC, GPIO_PIN_14);
    update_button(but_status, jitter_delay_start + 1, 1, GPIOB, GPIO_PIN_5);
    update_button(but_status, jitter_delay_start + 2, 2, GPIOB, GPIO_PIN_8);
    update_button(but_status, jitter_delay_start + 3, 3, GPIOA, GPIO_PIN_0);
    update_button(but_status, jitter_delay_start + 4, 4, GPIOC, GPIO_PIN_7);
    update_button(but_status, jitter_delay_start + 5, 5, GPIOC, GPIO_PIN_8);
    update_button(but_status, jitter_delay_start + 6, 6, GPIOA, GPIO_PIN_8);
    update_button(but_status, jitter_delay_start + 7, 7, GPIOC, GPIO_PIN_9);
    update_button(but_status, jitter_delay_start + 8, 8, GPIOA, GPIO_PIN_12);
    update_button(but_status, jitter_delay_start + 9, 9, GPIOB, GPIO_PIN_14);
    update_button(but_status, jitter_delay_start + 10, 10, GPIOB, GPIO_PIN_12);
    update_button(but_status, jitter_delay_start + 11, 11, GPIOA, GPIO_PIN_11);
    update_button(but_status, jitter_delay_start + 12, 12, GPIOC, GPIO_PIN_0);
    update_button(but_status, jitter_delay_start + 13, 13, GPIOC, GPIO_PIN_1);
    update_button(but_status, jitter_delay_start + 14, 14, GPIOC, GPIO_PIN_6);
    update_button(but_status, jitter_delay_start + 15, 15, GPIOB, GPIO_PIN_15);
    update_button(but_status, jitter_delay_start + 16, 16, GPIOB, GPIO_PIN_3);
    update_button(but_status, jitter_delay_start + 17, 17, GPIOC, GPIO_PIN_5);
    return 0;
}

int update_button(uint32_t* dest, uint32_t* start_timer, char offset, uint32_t port, uint32_t pin){
    if( time_delay(*start_timer, sys_tick) < 50 ) return 1;
    else{
        char but_val = gpio_input_bit_get(port, pin);
        *start_timer = sys_tick;
        if( but_val == 1) *dest |= 1 << offset;
        else *dest &= ~(1 << offset);
        return 0;
    }
}

void gpio_uinit(){
    //led
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    //buttons
    //DPAD: PC14, PB5, PB8, PA0
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    //4B: PC7, PC8, PA8, PC9
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    //CBUT: PA12, PB14, PB12, PA11
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    //BUMP: PC0, PC1, PC6, PB15
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
    //JSL_BUTTON: PB3
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    //JSR_BUTTON: PC5
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    //UART control: PB13
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    //bluetooth reset: B10
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    //power control: PB9
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    //battery voltage: PA5
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_5);


}
