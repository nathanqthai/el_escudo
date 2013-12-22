#ifndef EL_ESCUDO_H
#define EL_ESCUDO_H

// Includes
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// Pulse Width Definition
#define PULSE_WIDTH 10

// EL port definitions
#define A 0x04
#define B 0x08
#define C 0x10
#define D 0x20
#define E 0x40
#define F 0x80
#define G 0x01
#define H 0x02

// Class Definition
class EL_Escudo {
   private:
      void delay_ms(uint16_t);
      void delay_us(uint16_t);
      void wire_init(uint8_t);
      void wire_init_all();

   public:
      EL_Escudo();
      void wire_on(uint8_t);
      void wire_off(uint8_t);
      void wire_fade_in(uint8_t);
      void wire_fade_out(uint8_t);
      void status_init();
      void status_on();
      void status_off();
      void status_toggle();
};

#endif
