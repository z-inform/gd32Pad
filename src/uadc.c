#include "gd32f10x_adc.h"
#include "gd32f10x_dma.h"
#include "gd32f10x_gpio.h"
#include "../include/uadc.h"
#include "../include/utime.h"
extern uint32_t sys_tick;


void adc_uinit(){
    //LX - PA1  increase direction - right
    //LY - PA2  increase direction - up
    //RY - PA3  increase direction - down
    //RX - PA4  increase direction - left
    //BAT Voltage - PA5

    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_4);

    adc_deinit(ADC0);
    adc_mode_config(ADC_MODE_FREE);
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
    adc_dma_mode_enable(ADC0);
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 4);
    adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_1, ADC_SAMPLETIME_1POINT5);
    adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_2, ADC_SAMPLETIME_1POINT5);
    adc_regular_channel_config(ADC0, 2, ADC_CHANNEL_3, ADC_SAMPLETIME_1POINT5);
    adc_regular_channel_config(ADC0, 3, ADC_CHANNEL_4, ADC_SAMPLETIME_1POINT5);
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    adc_interrupt_enable(ADC0, ADC_INT_EOC);
    nvic_irq_enable(ADC0_1_IRQn, 2, 2);
    adc_enable(ADC0);
    uint32_t adc_startup = sys_tick;
    while( time_delay(adc_startup, sys_tick) < 10 ) {};
    adc_calibration_enable(ADC0);

}


void adc_dma_uinit(uint8_t *dst){
    dma_parameter_struct init;
    dma_struct_para_init(&init);
    dma_channel_disable(DMA0, DMA_CH0);
    dma_init(DMA0, DMA_CH0, &init);
    dma_circulation_enable(DMA0, DMA_CH0);
    dma_periph_address_config(DMA0, DMA_CH0, (uint32_t) 0x40012400 + 0x4C); //ADC0 data register
    dma_memory_address_config(DMA0, DMA_CH0, (uint32_t) dst);
    dma_periph_width_config(DMA0, DMA_CH0, DMA_PERIPHERAL_WIDTH_32BIT);
    dma_memory_width_config(DMA0, DMA_CH0, DMA_MEMORY_WIDTH_16BIT);
    dma_memory_increase_enable(DMA0, DMA_CH0);
    dma_periph_increase_disable(DMA0, DMA_CH0);
    dma_memory_to_memory_disable(DMA0, DMA_CH0);
    dma_priority_config(DMA0, DMA_CH0, DMA_PRIORITY_HIGH);
    dma_transfer_direction_config(DMA0, DMA_CH0, DMA_PERIPHERAL_TO_MEMORY);
    dma_transfer_number_config(DMA0, DMA_CH0, 4);
    dma_channel_enable(DMA0, DMA_CH0);
}

void ADC0_1_ISR(){
    adc_flag_clear(ADC0, ADC_FLAG_STRC);
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
}





