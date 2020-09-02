#include <avr/interrupt.h>  // thư viện cho các thao tác liên quan đến timer

// sử dụng 3641BS (common anode - chung cực dương)
//   A
//   _
// F|_|B
// E|G|C
//   - .DP
//   D
#define pA    12
#define pB    8
#define pC    5
#define pD    3
#define pE    2
#define pF    11
#define pG    6
#define pDP   4
void showAlpha(int num) // hàm này hiển thị chữ số, giá trị được kiểm tra của mỗi case là chữ số sẽ được hiển thị nếu case là đúng, code của mỗi case in chữ số là giá trị được kiểm tra của mỗi case 
{
  switch(num)
  {
    case 0:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, LOW); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, HIGH); 
      digitalWrite(pDP, HIGH);
      break;
    case 1:
      digitalWrite(pA, HIGH); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, HIGH); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, HIGH); 
      digitalWrite(pG, HIGH); 
      digitalWrite(pDP, HIGH);
      break;
    case 2:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, HIGH); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, LOW); 
      digitalWrite(pF, HIGH); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 3:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, HIGH); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 4:
      digitalWrite(pA, HIGH); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, HIGH); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 5:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, HIGH); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 6:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, HIGH); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, LOW); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 7:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, HIGH); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, HIGH); 
      digitalWrite(pG, HIGH); 
      digitalWrite(pDP, HIGH);
      break;
    case 8:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, LOW); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
    case 9:
      digitalWrite(pA, LOW); 
      digitalWrite(pB, LOW); 
      digitalWrite(pC, LOW); 
      digitalWrite(pD, LOW); 
      digitalWrite(pE, HIGH); 
      digitalWrite(pF, LOW); 
      digitalWrite(pG, LOW); 
      digitalWrite(pDP, HIGH);
      break;
  }
}

//  DIG1;DIG2;DIG3;DIG4
//   _   _   _   _
//  |_| |_| |_| |_|
//  |_|.|_|.|_|.|_|.
//
#define DIG1  13  // chu so hang nghin
#define DIG2  10  // chu so hang tram
#define DIG3  9   // chu so hang chuc
#define DIG4  7   // chu so hang don vi

long count = 0, countDIG = 0; // count là số giây trôi qua được hiển thị lên 4 LED 7 đoạn, countDIG để đếm số thứ tự LED 7 đoạn được hiển thị

void setup()
{
    pinMode(DIG1, OUTPUT); 
    pinMode(DIG2, OUTPUT); 
    pinMode(DIG3, OUTPUT); 
    pinMode(DIG4, OUTPUT); 
    pinMode(pA, OUTPUT); 
    pinMode(pB, OUTPUT); 
    pinMode(pC, OUTPUT); 
    pinMode(pD, OUTPUT); 
    pinMode(pE, OUTPUT); 
    pinMode(pF, OUTPUT); 
    pinMode(pG, OUTPUT); 
    pinMode(pDP, OUTPUT); 
 
    cli();                                  // tắt ngắt toàn cục
    
    // Reset Timer/Counter 1 
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    
    // Setup Timer/Counter 1 
    TCCR1B |= (1 << CS12);    // prescale = 256 -> f1 = 16000000/256 = 62500Hz -> T1 = 1/62500 s
    TCNT1 = 3036;             // thời gian giữa các lần ngắt của timer 1 = (65536 - 3036)*T1 = 1s
    TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable 

    // Reset Timer/Counter 2 
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;
    
    // Setup Timer/Counter 2
    TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));    // prescale = 1024  -> f2 = 16000000/1024 = 15625Hz -> T2 = 1/15625 s
    TCNT2 = 171;                                            // thời gian giữa các lần ngắt của timer 2 = thời gian mỗi LED 7 đoạn sáng trong 1 chu kỳ của mỗi LED 7 đoạn = (256 - 171)*T2 s
                                                            // -> chu kì của mỗi LED 7 đoạn = 4*(256 - 171)/15625 s
    TIMSK2 = (1 << TOIE2);                  // Overflow interrupt enable
     
    sei();                                  // cho phép ngắt toàn cục
}
 
void loop()
{
    
}
 
ISR (TIMER1_OVF_vect) 
{
    TCNT1 = 3036; // tiếp tục đếm từ 3036 để lại tràn xảy ra ngắt sau 1s 
    count = ((++count)%10000);  // cứ mỗi 1 giây tăng giá trị của count lên 1, khi count vượt quá 9999 thì cho count = 0 
}

ISR (TIMER2_OVF_vect) 
{
    TCNT2 = 171;  // tiếp tục đếm từ 171 để lại tràn xảy ra ngắt sau (256 - 171)/15625 s
    countDIG = ((++countDIG) % 4);  // countDIG = 0, 1, 2, 3 tương ứng với DIG4, DIG3, DIG2, DIG1
    switch(countDIG)
    {
      case 0: //  DIG4 sáng, các LED khác tắt
        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, LOW); 
        digitalWrite(DIG3, LOW); 
        digitalWrite(DIG4, HIGH);
        showAlpha(count%10);          // hiển thị chữ số hàng đơn vị
        break;
      case 1: //  DIG3 sáng, các LED khác tắt
        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, LOW); 
        digitalWrite(DIG3, HIGH); 
        digitalWrite(DIG4, LOW);
        showAlpha((count%100)/10);    // hiển thị chữ số hàng chục
        break;
      case 2: //  DIG2 sáng, các LED khác tắt
        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, HIGH); 
        digitalWrite(DIG3, LOW); 
        digitalWrite(DIG4, LOW);
        showAlpha((count%1000)/100);  // hiển thị chữ số hàng trăm
        break;
      case 3: //  DIG1 sáng, các LED khác tắt
        digitalWrite(DIG1, HIGH);
        digitalWrite(DIG2, LOW); 
        digitalWrite(DIG3, LOW); 
        digitalWrite(DIG4, LOW);
        showAlpha(count/1000);        // hiển thị chữ số hàng nghìn
        break;
    }
}
