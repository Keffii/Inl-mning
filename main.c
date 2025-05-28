#include <avr/io.h>
#include "gpio_driver.h"

// 20ms = 20
// 100ms = 100
// 500ms = 500
// 1second = 1000
// 2seconds = 2000

//Port number 0-13

int main(void) {
    init_blink(0, 0);
    while (1) {
        
    }
}