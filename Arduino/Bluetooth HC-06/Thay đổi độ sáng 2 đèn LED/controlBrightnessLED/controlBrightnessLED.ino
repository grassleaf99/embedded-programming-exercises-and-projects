#define LED0 3
#define LED1 6

//The circuit:
// * RX is digital pin 10 (connect to TX of HC-06)
// * TX is digital pin 11 (connect to RX of HC-06)

#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX
int brightness = 153;
int indexLED = 0;
char control;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  analogWrite(LED0, brightness);
  digitalWrite(LED1, LOW);
}

void loop() { // run over and over
  if (bluetooth.available()) 
  {
    control = bluetooth.read();
    switch(control)
    {
      case 'u':
      brightness = brightness + 51;
      if(brightness > 255)
      brightness = 255;
      break;
      case 'd':
      brightness = brightness - 51;
      if(brightness < 0)
      brightness = 0;
      break;
      case 'l':
      indexLED = 1;
      break;
      case 'r':
      indexLED = 0;
      break;
    }
  }
  if(indexLED)
  {
    analogWrite(LED1, brightness);
    digitalWrite(LED0, LOW);
  }
  else
  {
    analogWrite(LED0, brightness);
    digitalWrite(LED1, LOW);
  }
}
