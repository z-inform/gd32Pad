#pragma once

#include "stdint.h"

void uart_uinit(); //initializes uart
void uart_adc_uinit(uint16_t* src); //dma initialization for adc data send
void uart_com_send(char* str, int length); //dma init for string send

