// cực dương pin 9V gắn vào đầu 12V, cực âm pin 9V gắn vào đầu GND của L298N chỉ cung cấp năng lượng được cho 1 motor DC
// pin 9V chỉ cung cấp năng lượng cho 1 motor DC chạy được tốc độ lớn nhất là khoảng nửa tốc độ tối đa

#define POTENTIOMETER A0  // chân giữa của chiết áp nối với A0

#define ENA 11  // chân ENA của L298N gắn với chân digital 11 có thể tạo PWM
//#define ENB 9   // chân ENB của L298N gắn với chân digital 9 có thể tạo PWM
#define IN1 7   // chân IN1 của L298N gắn với chân digital 7
#define IN2 6   // chân IN2 của L298N gắn với chân digital 6
//#define IN3 5   // chân IN3 của L298N gắn với chân digital 5
//#define IN4 4   // chân IN4 của L298N gắn với chân digital 4 

//#define INTERRUPT0_SWITCH 2 // ngắt số 0 ở chân digital 2
#define INTERRUPT1_SWITCH 3 // ngắt số 1 ở chân digital 3

bool direction1 = false;
//bool direction2 = true;
void reverseDC1()
{
  direction1 = !direction1;
  digitalWrite(IN1, direction1);
  digitalWrite(IN2, !direction1);
}
/*void reverseDC2()
{
  direction2 = !direction2;
  digitalWrite(IN3, direction2);
  digitalWrite(IN4, !direction2);
}*/

int potentiometerVal, PWMval;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  //pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //pinMode(IN3, OUTPUT);
  //pinMode(IN4, OUTPUT);
  pinMode(INTERRUPT1_SWITCH, INPUT);
  attachInterrupt(1, reverseDC1, RISING);
  //pinMode(INTERRUPT0_SWITCH, INPUT);
  //attachInterrupt(0, reverseDC2, RISING);
  digitalWrite(IN1, direction1);
  digitalWrite(IN2, !direction1); 
  //digitalWrite(IN3, direction2);
  //digitalWrite(IN4, !direction2);
}

void loop() {
  // put your main code here, to run repeatedly:
  potentiometerVal = analogRead(POTENTIOMETER);
  PWMval = map(potentiometerVal, 0, 1023, 0, 255);
  analogWrite(ENA, PWMval);
  //analogWrite(ENB, PWMval);
  Serial.print("Motor đang chạy với (");
  Serial.print(PWMval);
  Serial.println("/255)*100% tốc độ");
}
