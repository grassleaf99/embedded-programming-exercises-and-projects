// code nay chac chan se sai neu giu nut nhan
// neu giu nut nhan thi chi co led gan vao chan E2 sang do ta quet led bang ham delay
// cu the la khi giu nut nhan, chuong trinh se cu o vong while(input == 0) va vi the, ham hien so ko dc goi lai, chi led dc cap nguon cuoi cung (led noi nguon toi chan E2) tu ham hien so duoc goi lan truoc hien so thoi 
// -> de khac phuc su co nay can dung timer
// -> dung timer hieu qua toi uu hon so voi delay
#include <main.h>
signed long g_x = 0;
void hienSoTangDan(signed long sotang);
int8 maled7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void main()
{
   set_tris_a(0xEF); // dat chan A4 làm output de cap nguon cho led 7 doan
   set_tris_e(0xF8); // dat chan E0, E1, E2 làm output de cap nguon cho led 7 doan
   set_tris_d(0x00); // dat tat ca cac chan cong D la output de lam sang den led 7 doan
   set_tris_b(0x03); // dat chan B0, B1 la input de dieu khien 2 nut nhan
   while(TRUE)
   {
      if(input(PIN_B0) == 0)  // neu nhan nut dc noi vao chan B0 thi tang g_x
      {
         delay_ms(2);
         if(input(PIN_B0) == 0)
         {
            while(input(PIN_B0) == 0) {}
            g_x++;
         }   
         if(g_x > 9999)
         g_x = 0;
      }
      if(input(PIN_B1) == 0)  // neu nhan nut dc noi vao chan B1 thi giam g_x
      {
         delay_ms(2);
         if(input(PIN_B1) == 0)
         {
            while(input(PIN_B1) == 0) {}
            g_x--;
         }   
         if(g_x < 0)
         g_x = 9999;
      }
      hienSoTangDan(g_x);
      //TODO: User Code
   }
}
void hienSoTangDan(signed long sotang)
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

