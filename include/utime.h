#pragma once

#include "stdint.h"

void clock_uinit();
void blink_timer_uinit(int delay);
uint32_t time_delay(uint32_t start, uint32_t now);
void usleep(uint32_t start, uint32_t delay);

