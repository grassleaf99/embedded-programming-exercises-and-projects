#define PHOTORESISTOR A0
#define LED_PWM 6
int sensorValue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PWM, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(PHOTORESISTOR);
  // cang sang, gia tri dien tro trong quang tro cang nho, khien cho V tai A0 cang nho, lam sensorValue cang nho
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
  analogWrite(LED_PWM, map(sensorValue, 20, 1023, 0, 255));
  // put your main code here, to run repeatedly:
  
}
