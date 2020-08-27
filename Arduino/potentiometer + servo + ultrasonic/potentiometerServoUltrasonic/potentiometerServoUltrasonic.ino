// project này dùng được cho việc giao tiếp cảm biến siêu âm
// khoảng cách đo của cảm biến siêu âm có thể tới 5m, hoạt động tốt trong vòng 3m
// dùng đối số thứ 3 (15000) được truyền vào hàm pulseIn() trong hàm measure() và hằng 50 ở biểu thức tính giá trị biến distance trong hàm measure() để xác định dùng cảm biến siêu âm để đo trong khoảng cách tối đa là 3m
// dùng dây male to female để gắn cảm biến siêu âm vào arduino
// chân GND của cảm biến siêu âm gắn vào chân GND của arduino
// chân Vcc của cảm biến siêu âm gắn vào chân 5V của arduino
// chân TRIG của cảm biến siêu âm gắn vào chân 7 của arduino
// chân ECHO của cảm biến siêu âm gắn vào chân 8 của arduino

#include <Servo.h>

#define SENSOR A0
#define SERVO_PIN 9
#define ECHO_PIN 8
#define TRIG_PIN 7
#define RED_LED 6

Servo myServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int positionServo = 0;    // variable to store the servo position

int sensorVal;  // lưu giá trị analogRead() đọc từ chiết áp

int realDistance;

void setup() {
  myServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  sensorVal = analogRead(SENSOR);
  positionServo = map(sensorVal, 0, 1023, 0, 180);
  myServo.write(positionServo);       // tell servo to go to position in variable 'positionServo'
  delay(15);                          // waits 15ms for the servo to reach the position
//  Serial.print("ADC of potentiometer is: ");
//  Serial.println(sensorVal);
//  Serial.print("Servo will go to ");
//  Serial.print(positionServo);
//  Serial.println(" degree");
//  Serial.println();
  realDistance = measure();
  Serial.println(realDistance);
  if(realDistance <= 2)
  digitalWrite(RED_LED, LOW);
  else
  if(realDistance > 2)
  analogWrite(RED_LED, map((303 - realDistance), 3, 300, 0, 255));
}

int measure() // hàm này trả về khoảng cách từ cảm biến siêu âm đến vật cản (theo cm), khoảng cách tối đa mà hàm measure() trả về là 300cm
{
  digitalWrite(TRIG_PIN, HIGH);
  digitalWrite(TRIG_PIN, LOW);
  int distance = pulseIn(ECHO_PIN, HIGH, 15000) / 50; // nếu xung không trở lại trong vòng 15000 micro giây, hàm pulseIn() sẽ trả về số 0
  // Hàm pulseIn() sẽ trả về số micro giây tương ứng với khoảng thời gian xung, hằng số 50 tức cứ 50 micro giây tương ứng 1cm
  // 15000 micro giây là khoảng thời gian tương ứng với phạm vi 3 mét ở hằng số 50 micro giây/ 1 cm
  return constrain(distance, 1, 300);
  // câu return trên có nghĩa là nếu giá trị trong biến distance nhỏ hơn 1 thì nó trả về 1, nếu giá trị trong biến distance lớn hơn 300 thì nó trả về 300
  // Để ý 1: 2cm (cũng như nhỏ hơn 2cm) là quá ngắn để cảm biến siêu âm đo được
  // Để ý 2: nếu không có vật cản trong khoảng cách mà cảm biến siêu âm có thể đo được, distance sẽ = 0 -> hàm measure() sẽ trả về 1
  // -> nếu hàm measure() trả về là 1 có nghĩa là cảm biến siêu âm không đo được gì (tức không thấy có vật cản trong khoảng 3cm đến 3m)
}
