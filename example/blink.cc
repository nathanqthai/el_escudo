#include "el_escudo.h"

int main (void) {
   EL_Escudo board;
   while(1) {
      board.wire_fade_in(A);
      board.wire_fade_out(A);
      board.status_toggle();
   }
   return 0;
}
