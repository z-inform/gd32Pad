#include "gd32f10x_rcu.h"
#include "gd32f10x_timer.h"

#include "../include/utime.h"

volatile uint32_t sys_tick = 1;

void blink_timer_uinit(int delay){
    rcu_periph_clock_enable(RCU_TIMER2);
    timer_deinit(TIMER2);
    timer_parameter_struct blink_timer;
    timer_struct_para_init(&blink_timer);
    blink_timer.prescaler = (rcu_clock_freq_get(CK_APB1) / 1000) - 1;
    blink_timer.alignedmode = TIMER_COUNTER_EDGE;
    blink_timer.counterdirection = TIMER_COUNTER_DOWN;
    blink_timer.period = delay;
    blink_timer.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER2, &blink_timer);
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    timer_enable(TIMER2);
    nvic_irq_enable(TIMER2_IRQn, 1, 1);
}

void clock_uinit(){
    rcu_osci_on(RCU_HXTAL);
    rcu_osci_stab_wait(RCU_HXTAL);
    rcu_hxtal_clock_monitor_enable();
    rcu_predv0_config(RCU_PREDV0_DIV2);
    rcu_pll_config(RCU_PLLSRC_HXTAL, RCU_PLL_MUL27);
    rcu_osci_on(RCU_PLL_CK);
    rcu_osci_stab_wait(RCU_PLL_CK);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV2);
    rcu_apb2_clock_config(RCU_APB1_CKAHB_DIV1);
    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
    SysTick_Config(rcu_clock_freq_get(CK_SYS) / 1000 - 1);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
}

void TIM3_IRQHandler(){
    gpio_bit_write(GPIOC, GPIO_PIN_10, !gpio_output_bit_get(GPIOC, GPIO_PIN_10));
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
}

uint32_t time_delay(uint32_t start, uint32_t now){
    if( start < now ) return now - start;
    else return 0xFFFFFFFF - start + now;
}

void SysTick_Handler(){
    sys_tick += 1;
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
}
