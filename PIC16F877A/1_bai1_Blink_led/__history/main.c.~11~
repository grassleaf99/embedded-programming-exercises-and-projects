#include <main.h>

void main()
{
   set_tris_d(0x00); // cài dat port D làm output vì doi so truyên vào là 0x00000000 mà 0 cua tris có nghia là out tuc xuat du liêu -> tât ca các chan (bit) cua cong D deu là xuat du lieu 
   while(TRUE)
   {
      output_d(0xFE); // den led tuong ung voi bit D0 (chan  RD0) sang
      delay_ms(1000);    // tam dung chuong trinh 1000 ms = 1s (tham so truyen vao là ms)
      output_d(0x00); // tat ca den deu sang
      delay_ms(1000);
      output_d(0x55); // den led tuong ung voi bit D1, D3, D5, D7 sáng
      delay_ms(1000);
      output_d(0xFF); // tat ca den deu tat
      delay_ms(1000);
   }

}
