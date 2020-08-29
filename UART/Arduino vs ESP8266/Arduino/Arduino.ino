//The circuit:
// * RX is digital pin 10 
// * TX is digital pin 11 

#include <SoftwareSerial.h>

SoftwareSerial ntUART(10, 11); // RX, TX

#define LED 5
volatile uint8_t brightness = 125;

void setup() {
  ntUART.begin(115200);
  DDRD |= 1<<LED;
}

void loop() { // run over and over
  if (ntUART.available()) // nếu có dữ liệu từ ESP8266
  {
    brightness = ntUART.read();  // đọc dữ liệu rồi gán cho biến brightness
  }
  analogWrite(LED, brightness);
}
