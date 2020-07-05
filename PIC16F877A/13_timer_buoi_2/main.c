#include <main.h>
long count = 0;
void main()
{
   set_tris_d(0x80);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);    // chon clock noi = 20M/4 = 5MHz va che do chia cho 8 -> moi lan tang 1 bit se co tan so 5000kHz/8 = 8/5000 (ms)
   set_timer1(64911);                           // cai dat dem tu 64911 -> 65536 (2 mu 16) --> thoi gian xay ra tran timer1 (su kien ngat) la: (65536 - 64911) * (8/5000) = 1 ms  
   enable_interrupts(INT_TIMER1);               // kich hoat ngat timer 1
   enable_interrupts(GLOBAL);                   // kich hoat ngat toan cuc
   while(TRUE)
   {
      //TODO: User Code
   }

}

#INT_TIMER1
void chuyenled()
{
     set_timer1(64911);                         // cai dat dem tu 64911 de xay ra tran sau 1 ms
     count++;
     if(count == 1000)
     {
         count = 0;
         output_toggle(PIN_D7);
     }
}
