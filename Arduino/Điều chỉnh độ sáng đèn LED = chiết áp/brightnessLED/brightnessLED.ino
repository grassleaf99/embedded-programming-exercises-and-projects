#define SENSOR A0
#define LED_PIN 6

int sensorVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(SENSOR);
  analogWrite(LED_PIN, map(sensorVal, 0, 1023, 0, 255));
  Serial.println(sensorVal);
}
