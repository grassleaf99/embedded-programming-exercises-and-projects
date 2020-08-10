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
  if (bluetooth.available()) 
  {
    Serial.write(bluetooth.read());
  }
  if (Serial.available()) 
  {
    bluetooth.write(Serial.read());
  }
}
