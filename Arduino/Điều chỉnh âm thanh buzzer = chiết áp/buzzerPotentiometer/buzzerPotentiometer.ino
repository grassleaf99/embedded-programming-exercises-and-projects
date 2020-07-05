#define SENSOR A0
#define BUZZER_PIN 8

int sensorVal;

void setup() {
  // put your setup code here, to run once:
  // khong can pinMode cho pin su dung ham tone()
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(SENSOR);
  tone(BUZZER_PIN, map(sensorVal, 0, 1023, 31, 4978));
  Serial.println(sensorVal);
}
