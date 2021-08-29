#pragma once

#include "stdint.h"

void gpio_uinit();
int get_buttons(uint32_t* but_status);
int update_button(uint32_t* dest, uint32_t* start_timer, char count, uint32_t port, uint32_t pin);

