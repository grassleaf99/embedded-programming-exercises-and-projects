//The circuit:
// * RX is digital pin 10 (connect to TX of HC-06)
// * TX is digital pin 11 (connect to RX of HC-06)

#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() { // run over and over
  if (bluetooth.available()) // nếu HC-06 gửi dữ liệu
  {
    Serial.write(bluetooth.read()); // hiển thị dữ liệu từ HC-06 lên Serial theo từng byte
  }
  if (Serial.available())   // nếu ta đã gửi dữ liệu gì đó lên Serial
  {
    bluetooth.write(Serial.read()); // dữ liệu đó được gửi cho HC-06 theo từng byte
  }
}
