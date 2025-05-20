#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

//Initialize blink on chosen pin number and time
void init_blink(uint8_t pin, uint16_t ms);

#endif