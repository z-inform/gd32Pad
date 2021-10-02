#pragma once

#include "stdint.h"

void uart_uinit(); //initializes uart
void uart_dma_uinit(); //dma initialization for adc data send
void uart_data_send(char* str, int length); //send raw data
void uart_packet_send(char* str, int length, char type); //form a packet and send through uart

