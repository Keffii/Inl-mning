#include <util/delay.h>
#include <time.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//Global pointers to port and ddr
static volatile uint8_t* blink_port;
static volatile uint8_t* blink_ddr;
static uint8_t blink_bit;

void init_blink(uint8_t pin, uint16_t ms) {
    // Initalize correct pin to output
    if(pin <= 7){
        blink_port = &PORTD;
        blink_ddr = &DDRD;
        blink_bit = pin;
    } else if(pin <= 13){
        blink_port = &PORTB;
        blink_ddr = &DDRB;
        blink_bit = pin - 8;
    }else{
        //Incorrect pin number
        return;
    }

    //Pin as output
    *blink_ddr |= (1 << blink_bit);

    // Timer1 in CTC-mode
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    //Choose prescaler and OCRA1 depending on the ms
    uint16_t ocr = 0;
    uint8_t prescaler_bits = 0;
    if (ms == 20)      { ocr = 1249; prescaler_bits = (1 << CS12); }         // 256
    else if (ms == 100){ ocr = 6249; prescaler_bits = (1 << CS12); }         // 256
    else if (ms == 500){ ocr = 31249; prescaler_bits = (1 << CS12); }        // 256
    else if (ms == 1000){ ocr = 62499; prescaler_bits = (1 << CS12); }       // 256
    else if (ms == 2000){ ocr = 31249; prescaler_bits = (1 << CS12) | (1 << CS10); } // 1024
    else { ocr = 1249; prescaler_bits = (1 << CS12); } // default 20ms

    OCR1A = ocr;
    TCCR1B |= (1 << WGM12); // CTC
    TCCR1B |= prescaler_bits;
    TIMSK1 |= (1 << OCIE1A); // Enable interrupt
    sei(); //Activate global interrupts
}

ISR(TIMER1_COMPA_vect) {
    // Toggle chosen pin
    *blink_port ^= (1 << blink_bit);
}