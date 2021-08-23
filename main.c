#include "gd32f10x_libopt.h"
#include "gd32f10x_rcu.c"
#include "gd32f10x_gpio.c"
#include "gd32f10x_adc.h"

void clock_init();

int main(void){
    clock_init();
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);
    gpio_bit_set(GPIOC, GPIO_PIN_10);

    while(1){
    volatile uint32_t clock;
    clock = rcu_system_clock_source_get();
    clock -= RCU_CKSYSSRC_PLL;
    };
}

void clock_init(){
    rcu_osci_on(RCU_HXTAL);
    rcu_predv0_config(RCU_PREDV0_DIV2);
    rcu_pll_config(RCU_PLLSRC_HXTAL, RCU_PLL_MUL27);
    rcu_hxtal_clock_monitor_enable();
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV2);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
    rcu_osci_stab_wait(RCU_HXTAL);
    rcu_periph_clock_enable(RCU_GPIOC);
}
