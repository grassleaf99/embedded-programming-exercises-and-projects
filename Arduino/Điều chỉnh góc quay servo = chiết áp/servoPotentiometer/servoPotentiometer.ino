#include <Servo.h>

#define SENSOR A0
#define SERVO_PIN 9

Servo myServo;  // create servo object to control a servo
int sensorVal;  // lưu giá trị analogRead() đọc từ chiết áp
int positionServo; // variable to store the servo position

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(SENSOR);
  positionServo = map(sensorVal, 0, 1023, 0, 180);
  myServo.write(positionServo);       // tell servo to go to position in variable 'positionServo'
  delay(15);                          // waits 15ms for the servo to reach the position
  Serial.print("ADC of potentiometer is: ");
  Serial.println(sensorVal);
  Serial.print("Servo will go to ");
  Serial.print(positionServo);
  Serial.println(" degree");
  Serial.println();
}
