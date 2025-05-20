#include <avr/io.h>
#include "gpio_driver.h"

//20ms = prescaler = 256 & 1249
//100ms = prescaler = 256 & 6249
//500ms = prescaler = 256 & 31249
// 1sek = prescaler = 256 & 62459
// 2sek = prescaler = 1024 & 31249

// 20ms = 20
// 100ms = 100
// 500ms = 500
// 1second = 1000
// 2seconds = 2000

//Port number 0-13

int main(void) {
    init_blink(0, 500); //Pin 13, 1sekund
    while (1) {
        // Ingenting behövs i huvudloopen
    }
}