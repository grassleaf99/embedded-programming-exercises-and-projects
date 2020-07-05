#include <main.h>

void main()
{
//!   set_tris_d(0x00);
//!   int8 arr[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
//!   while(TRUE)   // cach 1: su dung mang (nhuoc diem ton thoi gian)
//!  {
//!     for(int i = 0; i < 8; i++)
//!     {
//!         output_d(arr[i]);
//!         delay_ms(1000);
//!     }
//!  }
// cach 2: dich bit
// cach nay con ap dung viec su dung chan ki hieu so nhung a Tuyen bao kho cho nguoi khac hieu code
   set_tris_d(0x00);
   int8 x;
   while(TRUE)
   {
      for(int i = 0; i < 8; i++)
      {
         x = 0xFE;
         x = x << i;
         output_d(x);
         for(int j = 0; j < i; j++)
         output_high(64 + j);      // 64 la chan D0
         delay_ms(500);
      }
      // cach 3: chi dung dich bit
//!      int8 x = 0xFE;
//!      output_d(x);
//!      delay_ms(500);
//!      for(int i = 0; i < 7; i++)
//!      {
//!         x = (x << 1) | 0x01;
//!         output_d(x);
//!         delay_ms(500);
//!      }
   }
}
