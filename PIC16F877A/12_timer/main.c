#include <main.h>
int8 maled7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
int16 count_isr = 0;
int16 count = 0;
void hienSoTangDan(int16 sotang)
{  
         output_low(PIN_A4);
         output_high(PIN_E0);
         output_high(PIN_E1);
         output_high(PIN_E2);
         output_d(maled7[sotang / 1000]);
         delay_ms(5);
         output_low(PIN_E0);
         output_high(PIN_A4);
         output_high(PIN_E1);
         output_high(PIN_E2);
         output_d(maled7[(sotang % 1000) / 100]);
         delay_ms(5);
         output_low(PIN_E1);
         output_high(PIN_E0);
         output_high(PIN_A4);
         output_high(PIN_E2);
         output_d(maled7[((sotang % 1000) % 100) / 10]);
         delay_ms(5);
         output_low(PIN_E2);
         output_high(PIN_E0);
         output_high(PIN_E1);
         output_high(PIN_A4);
         output_d(maled7[((sotang % 1000) % 100) % 10]);
         delay_ms(5);
}
void main()
{
   setup_timer_0(T0_INTERNAL | T0_DIV_32); // thiet lap timer 0 l� hoac cua 2 cai sau
                                           // clock n�i: T0_INTERNAL (d�ng 152) -> xung l� 20M/4 = 5MHz = 5000KHz
                                           // ch� d� chia 32 (dong 161) tuc timer 0 dem t� 0 -> 256, moi 1 lan tang 1 don vi mat khoang thoi gian l� 32/5000(ms)
   set_timer0(61);                         // c�i dat timer 0 d�m tu 61 -> 256 -> timer 0 se d�m trong khoang thoi gian 32/5000(ms) * (256 - 61) = 1,248 ms 
   enable_interrupts(INT_TIMER0);          // enable ngat tr�n timer 0
   enable_interrupts(GLOBAL);              // enable ngat toan cuc
   while(TRUE)
   {
      //TODO: User Code
      hienSoTangDan(count);                // tang len 1 don vi sau 0,1248 s
   }
}
#INT_TIMER0
void timer0_isr(void)                      // ham nay tu dong dc goi khi timer 0 xay ra tr�n (tuc su kien ngat)
{
   set_timer0(61);                         // v� timer 0 se ti�p tuc dem sau khi su kien ngat xay ra n�n d� timer 0 d�m trong khoang thoi gian nhu cu (1,248 ms), can cau lenh d�ng n�y de cai dat timer 0 dem tu 61 -> 256
   count_isr++;
   if(count_isr == 100)                    // khi timer 0 dem tr�n 100 l�n (t�c sau 100 * 1,248ms = 0,1248s), s� duoc hi�n thi se tang 1 don vi 
   {
      count++;
      count_isr = 0;
   }
   if(count == 10000)
   count = 0;
}
