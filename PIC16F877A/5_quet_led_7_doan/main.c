#include <main.h>

void main()
{
   set_tris_a(0xEF);
   set_tris_e(0xF8);
   set_tris_d(0x00);
   int8 maled7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
   while(TRUE)
   {
         output_low(PIN_A4);
         output_high(PIN_E0);
         output_high(PIN_E1);
         output_high(PIN_E2);
         output_d(maled7[1]);
         delay_ms(5);
         output_low(PIN_E0);
         output_high(PIN_A4);
         output_high(PIN_E1);
         output_high(PIN_E2);
         output_d(maled7[2]);
         delay_ms(5);
         output_low(PIN_E1);
         output_high(PIN_E0);
         output_high(PIN_A4);
         output_high(PIN_E2);
         output_d(maled7[3]);
         delay_ms(5);
         output_low(PIN_E2);
         output_high(PIN_E0);
         output_high(PIN_E1);
         output_high(PIN_A4);
         output_d(maled7[4]);
         delay_ms(5);
      //TODO: User Code
   }

}
