#include "../include/uprotocol.h"
#include "gd32f10x_usart.h"
#include "gd32f10x_dma.h"
#include "stdint.h"
#include "../include/circ_buffer.h"
#include "../include/CRC32.h"
#include "string.h"
#include "gd32f10x_crc.h"
#include "stdlib.h"

extern circ_buffer uart_read;
extern char connected_state;

void uart_uinit(){
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_baudrate_set(USART0, 115200);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    nvic_irq_enable(USART0_IRQn, 1, 3);

    usart_dma_receive_config(USART0, USART_DENR_ENABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_enable(USART0);
}

void uart_dma_uinit(){
    dma_parameter_struct init;
    dma_struct_para_init(&init);

    dma_channel_disable(DMA0, DMA_CH3);
    dma_init(DMA0, DMA_CH3, &init);
    dma_circulation_disable(DMA0, DMA_CH3);
    dma_periph_address_config(DMA0, DMA_CH3, (uint32_t) 0x40013800 + 0x04); //USART data register
    dma_periph_width_config(DMA0, DMA_CH3, DMA_PERIPHERAL_WIDTH_32BIT);
    dma_memory_width_config(DMA0, DMA_CH3, DMA_MEMORY_WIDTH_8BIT);
    dma_memory_increase_enable(DMA0, DMA_CH3);
    dma_periph_increase_disable(DMA0, DMA_CH3);
    dma_memory_to_memory_disable(DMA0, DMA_CH3);
    dma_priority_config(DMA0, DMA_CH3, DMA_PRIORITY_ULTRA_HIGH);
    dma_transfer_direction_config(DMA0, DMA_CH3, DMA_MEMORY_TO_PERIPHERAL);

}

void uart_data_send(char* str, int length){
    while( !usart_flag_get(USART0, USART_FLAG_TBE) || dma_transfer_number_get(DMA0, DMA_CH3)){} //check for ongoing transmission
        dma_channel_disable(DMA0, DMA_CH3);
        usart_dma_receive_config(USART0, USART_DENT_ENABLE);
        usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
        dma_memory_address_config(DMA0, DMA_CH3, (uint32_t) str);
        dma_transfer_number_config(DMA0, DMA_CH3, length);
        dma_channel_enable(DMA0, DMA_CH3);
}

void USART0_ISR(){
    if( usart_flag_get(USART0, USART_FLAG_RBNE) ){
        circ_write(USART_DATA(USART0), &uart_read);
        usart_flag_clear(USART0, USART_FLAG_RBNE);
    }
}


void uart_packet_send(char *str, int length, char type){
    //packet format
    //2 bytes: 0x3B3D - start of message
    //2 bytes: data count (bytes)
    //1 byte: data type (buttons, status...)
    //... bytes: data (always 0 padded to 4 byte alignment)
    //crc32 of data

    int crc_length = length + (4 - (length % 4));
    uint32_t* crc_buf = calloc(crc_length, 1);
    memcpy(crc_buf, str, length); //save copy of data to buffer and pad with zeroes to uint32 alingment
    char* buf = (char*) malloc(5 + crc_length + 4);
    memcpy(buf + 5, crc_buf, crc_length); //copy padded data to final parcel buffer
    crc_buf[0] = doCRC32(crc_buf, crc_length);
    memcpy(buf + 2, &crc_length, 2); //copy padded data length to parcel
    memcpy(buf + 5 + crc_length, crc_buf, 4); //copy crc32 of data to parcel

    buf[0] = 0x3B; //set parcel prefix
    buf[1] = 0x3D;
    buf[4] = type; //set data type

    uart_data_send(buf, 5 + crc_length + 4);
    free(crc_buf);
    free(buf);
}
