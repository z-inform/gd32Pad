#include "gd32f10x_libopt.h"
#include "gd32f10x_rcu.c"
#include "gd32f10x_gpio.c"
#include "gd32f10x_misc.c"

void clock_uinit();
void adc_uinit();
void gpio_uinit();
int get_buttons(uint32_t* but_status);
int update_button(uint32_t* dest, uint32_t* start_timer, char count, uint32_t port, uint32_t pin);
uint32_t sys_tick();

int main(void){
    clock_uinit();
    gpio_uinit();

    while(1){
        if (gpio_input_bit_get(GPIOC, GPIO_PIN_9) == 0){
            gpio_bit_reset(GPIOC, GPIO_PIN_10);
        }
        else gpio_bit_set(GPIOC, GPIO_PIN_10);
    }
}

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
    update_button(but_status, jitter_delay_start + 15, 15, GPIOB, GPIO_PIN_12);
    update_button(but_status, jitter_delay_start + 16, 16, GPIOB, GPIO_PIN_3);
    update_button(but_status, jitter_delay_start + 17, 17, GPIOC, GPIO_PIN_5);
    return 0;
}

int update_button(uint32_t* dest, uint32_t* start_timer, char offset, uint32_t port, uint32_t pin){
    uint32_t delta = sys_tick() - *start_timer;
    if( delta < 0 ) delta = 0xFFFFFFFF + delta;
    if( delta < 50 ) return 1;
    else{
        char but_val = gpio_input_bit_get(port, pin);
        *start_timer = sys_tick();
        if( but_val == 1) *dest |= 1 << offset;
        else *dest &= ~(1 << offset);
    return 0;
    }
}

void gpio_uinit(){
    //led
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_bit_set(GPIOC, GPIO_PIN_10);
    //buttons
    //DPAD: PC14, PB5, PB8, PA0
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    //4B: PC7, PC8, PA8, PC9
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    //CBUT: PA12, PB14, PB12, PA11
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    //BUMP: PC0, PC1, PC6, PB12
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    //JSL_BUTTON: PB3
    gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    //JSR_BUTTON: PC5
    gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
}

void adc_uinit(){
}

void clock_uinit(){
    rcu_osci_on(RCU_HXTAL);
    rcu_predv0_config(RCU_PREDV0_DIV2);
    rcu_pll_config(RCU_PLLSRC_HXTAL, RCU_PLL_MUL27);
    rcu_hxtal_clock_monitor_enable();
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV2);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
    rcu_osci_stab_wait(RCU_HXTAL);
    systick_clksource_set(SYSTICK_CLKSOURCE_HCLK_DIV8);
    SysTick_Config(rcu_clock_freq_get(CK_SYS) / 8000);
    rcu_periph_clock_enable(RCU_GPIOC);
}

uint32_t sys_tick(){
    return SysTick->VAL;
}
