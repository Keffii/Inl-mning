#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "gpio_driver.h"

// init_blink(pin nummer, angiven tid 20, 100, 500, 1s, 2s)
//DDRB |= (1 << PB3)
//PORTB_

//OCRA1

//20ms = prescaler = 256 & 1249
//100ms = prescaler = 256 & 6249
//500ms = prescaler = 256 & 31249
// 1sek = prescaler = 256 & 62459
// 2sek = prescaler = 1024 & 31249

int main(void) {
    init_blink(13, 1000); //Pin 13, 1sekund
    uart_init(103);   // 9600 baud @ 16 MHz → UBRR = 103
    timer1_init();
    sei();            // Aktivera globala avbrott

    while (1) {
        // Ingenting behövs i huvudloopen
    }
}