#include <main.h>
signed long g_x = 0;
int8 maled7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// RB la ngat lien quan den cac thay doi cac chan B4 -> B7
// sau dong 6 phai la ham ngat, câu lênh cua dong 6 chi duoc ghi 1 lan, nêu ghi quá 1 lân se gây ra xung dôt (tuc la sai)
#INT_RB      // ngat RB - ngat lien quan den cac thay doi chan B4 -> B7
void taGia() // khi ân nút nhân nôi voi chan B4 hay chan B5 thì dó là su kien ngat, khi dó trình phuc vu ngat (chuong trinh ngat) tu dông thuc hien 
{
   if(input(PIN_B4) == 0)   // nut nhan nói vói chân B4 duoc án
   {
      g_x++;
      if(g_x > 9999)
      g_x = 0;
   }
   if(input(PIN_B5) == 0)   // nut nhan nói vói chân B5 duoc án
   {
      g_x--;
      if(g_x < 0)
      g_x = 9999;
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
void main()
{
   set_tris_a(0xEF); // dat chan A4 làm output de cap nguon cho led 7 doan
   set_tris_e(0xF8); // dat chan E0, E1, E2 làm output de cap nguon cho led 7 doan
   set_tris_d(0x00); // dat tat ca cac chan cong D la output de lam sang den led 7 doan
   set_tris_b(0x30); // dat chan B4 va B5 la input de lay du lieu nut nhan. nhan nut noi voi B4 thi tang so, nhan nut noi voi B5 thi giam so
   enable_interrupts(INT_RB); // enable kieu ngat RB - ngat lien quan den cac thay doi chan B4 -> B7
   enable_interrupts(GLOBAL); // enable ngat toan cuc
   while(TRUE)
   {  
      hienSoTangDan(g_x); 
   }

}
