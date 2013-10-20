#include "el_escudo.h"

// PRIVATE FUNCTIONS BEGIN
// delay_ms
// INPUT:
//    uint16_t count - number of milliseconds to delay
// OUTPUT:
//    none
// DESCRIPTION:
//    works around _delay_ms only taking compile time constants
void EL_Escudo::delay_ms(uint16_t count) {
   while(count--) {
      _delay_ms(1);
   }
}

// delay_us
// INPUT:
//    uint16_t count - number of microseconds to delay
// OUTPUT:
//    None
// DESCRIPTION:
//    works around _delay_us only taking compile time constants
void EL_Escudo::delay_us(uint16_t count) {
   while(count--) {
      _delay_us(1);
   }
}

// init
// INPUT:
//    uint8_t wires - el wires to initialize
// OUTPUT:
//    none
// DESCRIPTION:
//    takes wire letter(s) (A-H) and initializes them as outputs
//    sets them low by default
void EL_Escudo::wire_init(uint8_t wires) {
   DDRD |= (wires & (A | B | C | D | E | F));
   DDRB |= (wires & (G | H));

   wire_off(wires);
}

// delay_ms
// INPUT:
//    none
// OUTPUT:
//    npne
// DESCRIPTION:
//    initializes all EL wires
void EL_Escudo::wire_init_all(void) {
   wire_init(A | B | C | D | E | F | G | H);
}
// PRIVATE FUNCTIONS END

// PUBLIC FUNCTIONS BEGIN

// EL_Escudo
// INPUT:
//    none
// OUTPUT:
//    none
// DESCRIPTION:
//    constructor that initializes all el wires and the status led
EL_Escudo::EL_Escudo() {
   wire_init_all();
   status_init();
}

// wire_on
// INPUT:
//    uint8_t wires - wires to turn on
// OUTPUT:
//    none
// DESCRIPTION:
//    turns on an el wire
void EL_Escudo::wire_on(uint8_t wires) {
   PORTD |= (wires & (A | B | C | D | E | F));
   PORTB |= (wires & (G | H));
}

// wire_off
// INPUT:
//    uint8_t wires - wires to turn off
// OUTPUT:
//    none
// DESCRIPTION:
//    turns off an el wire
void EL_Escudo::wire_off(uint8_t wires) {
   PORTD &= ~(wires & (A | B | C | D | E | F));
   PORTB &= ~(wires & (G | H));
}

// wire_fade_in
// INPUT:
//    uint8_t wires - wires to turn fade in
// OUTPUT:
//    none
// DESCRIPTION:
//    uses manual pwm to cause an el wire to fade in
//    TODO: allow user to select brightness and duration
void EL_Escudo::wire_fade_in(uint8_t wires) {
   for(int brightness = 0; brightness < PULSE_WIDTH; brightness++) {
      for(int duration = 0; duration < 5; duration++) {
         wire_on(wires);
         delay_ms(brightness);

         wire_off(wires);
         delay_ms(PULSE_WIDTH-brightness);
      }
   }
}

// wire_fade_out
// INPUT:
//    uint8_t wires - wires to turn fade out
// OUTPUT:
//    none
// DESCRIPTION:
//    uses manual pwm to cause an el wire to fade out
//    TODO: allow user to select brightness and duration
void EL_Escudo::wire_fade_out(uint8_t wires) {
   for(int brightness = PULSE_WIDTH; brightness > 0; brightness--) {
      for(int duration = 0; duration < 5; duration++) {
         wire_on(wires);
         delay_ms(brightness);

         wire_off(wires);
         delay_ms(PULSE_WIDTH-brightness);
      }
   }
}

// status_init
// INPUT:
//    none
// OUTPUT:
//    none
// DESCRIPTION:
//    initializes the status indicator led
void EL_Escudo::status_init(void) {
   DDRB |= _BV(DDB5);
   PORTB &= ~_BV(DDB5);
}

// status_on
// INPUT:
//    none
// OUTPUT:
//    none
// DESCRIPTION:
//    turns status indicator led on
void EL_Escudo::status_on(void) {
   PORTB |= _BV(DDB5);
}

// status_off
// INPUT:
//    none
// OUTPUT:
//    none
// DESCRIPTION:
//    turns status indicator led off
void EL_Escudo::status_off(void) {
   PORTB &= ~_BV(DDB5);
}

// status_toggle
// INPUT:
//    none
// OUTPUT:
//    none
// DESCRIPTION:
//    toggles status indicator led
void EL_Escudo::status_toggle(void) {
   PORTB ^= _BV(DDB5);
}
