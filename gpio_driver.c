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



// void blinkSetup(){
//   //noInterrupts();
//   // Clear registers
//   TCCR1A = 0;
//   TCCR1B = 0;
//   TCNT1 = 0;

//   // 250 Hz (16000000/((249+1)*256))
//   OCR1A = 249;

//   // 50 Hz (16000000/((1249+1)*256))
//   // OCR1A = 1249

//   // 20ms --> 50Hz
//   // 100ms --> 10Hz
//   // 500ms --> 2Hz
//   // 1 sec --> 1Hz
//   // 2 sec --> 0.5Hz
  
//   // CTC
//   TCCR1B |= (1 << WGM12);
//   // Prescaler 256
//   TCCR1B |= (1 << CS12);
//   // Output Compare Match A Interrupt Enable
//   TIMSK1 |= (1 << OCIE1A);
//   //interrupts();
// }

/* // HÄR VÄLJS PINNE OCH VILKEN SETUP DEN SKA HA. 
// TA REDA PÅ ISR!!!!!!!
void setup() {
  pinMode(ledPin, 0);
  setupTimer1();
}
*/


// int main(void) {
//     int8_t PIN_NUMBER = 0;
//     int8_t PORT;
//     int8_t BIT;

//     if (PIN_NUMBER == 0){
//         DDRD |= (1 <<DDD0);
//         PORT = PORTD;
//         BIT = PD0;
//     }
//     else if (PIN_NUMBER == 1)
//     {        
//         DDRD |= (1 <<DDD1);
//     }
//     else if (PIN_NUMBER == 2)
//     {        
//         DDRD |= (1 <<DDD2);
//     }
//     else if (PIN_NUMBER == 3)
//     {        
//         DDRD |= (1 <<DDD3);
//     }
//     else if (PIN_NUMBER == 4)
//     {        
//         DDRD |= (1 <<DDD4);
//     }
//     else if (PIN_NUMBER == 5)
//     {        
//         DDRD |= (1 <<DDD5);
//     }
//     else if (PIN_NUMBER == 6)
//     {        
//         DDRD |= (1 <<DDD6);
//     }
//     else if (PIN_NUMBER == 7)
//     {        
//         DDRD |= (1 <<DDD7);
//     }
//     else if (PIN_NUMBER == 8)
//     {        
//         DDRB |= (1 <<DDB0);
//     }
//     else if (PIN_NUMBER == 9)
//     {        
//         DDRB |= (1 <<DDB1);
//     }
//     else if (PIN_NUMBER == 10)
//     {        
//         DDRB |= (1 <<DDB2);
//     }
//     else if (PIN_NUMBER == 11)
//     {        
//         DDRB |= (1 <<DDB3);
//     }
//     else if (PIN_NUMBER == 12)
//     {        
//         DDRB |= (1 <<DDB4);
//     }
//     else if (PIN_NUMBER == 13)
//     {        
//         DDRB |= (1 <<DDB5);
//     }

//     // blink_init(10, 20); // Pinne 10 ska bli aktiverad som output,
//     // blink_start();
    
//     // SÅ HÄR VILL SEBASTIAN KUANNA SKRIKA
//     // blink_init(5, 100);
//     while (1) {
//         PORTB |= (1 <<DDB5);
//         _delay_ms(1000);
//          PORTB &= ~(1 <<DDB5);
//          _delay_ms(1000);
//     }
// }