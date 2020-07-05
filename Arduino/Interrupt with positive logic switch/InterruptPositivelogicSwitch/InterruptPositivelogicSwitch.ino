#define INTERRUPT_SWITCH 2
#define LED 7

boolean light = false;

void reverseLED()
{
  delay(5); // nut nhan co the bi nhieu trong toi da 5 ms ke tu khi nhan nut
  light = !light;
  digitalWrite(LED, light);
  delay(5); // nut nhan co the bi nhieu trong toi da 5 ms ke tu khi tha nut
}

void setup() {
  // put your setup code here, to run once:
  pinMode(INTERRUPT_SWITCH, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, light); 
  attachInterrupt(0, reverseLED, RISING); // tham số đầu tiên là số thứ tự của ngắt, 0 là số thứ tự ngắt nối với chân digital số 2, 1 là số thứ tự ngắt nối với chân digital số 3
  // tham số thứ 2 là hàm sẽ được thực thi khi điều kiện ngắt xảy ra, hàm đó được gọi là ISR (interrupt service routine)
  // tham số thứ 3 là điều kiện xảy ra ngắt
  // vì ta muốn ngắt xảy ra khi ấn nút, mà mạch nút nhấn của project này là nút nhấn logic dương (khi ấn nút nhấn thì logic nút nhấn là HIGH)
  // -> điều kiện xảy ra ngắt là từ LOW -> HIGH, tức là RISING
}

void loop() {
  
  // put your main code here, to run repeatedly:
}
