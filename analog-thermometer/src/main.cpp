#define ServoPin D4
#define DhtPin D2
#define DhtType DHT22

#include <Servo.h>
#include <DHT.h>

Servo myServo;
DHT dht(DhtPin, DhtType);

float temp = 0.00f;
float lastTemp = 0.00f;


bool hasTemperatureChanged() {
  if(temp != lastTemp) {
    lastTemp = temp;
    return true;
  }
  return false;
}


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int calcServoMovement() {
  // Remove measuring failure by adding offset.
  float calibratedTemp = temp + 5.0f;

  Serial.println("(calibrated): " + String(calibratedTemp));
  
  // 0 degree and 180 degree are reversed in my case because of servo positioning.
  int degreeFloat = mapFloat(calibratedTemp, 15.0f, 25.0f, 180.0f, 0.0f);
  return (int)round(degreeFloat);
}


void setup() {
  Serial.begin(9600);
  myServo.attach(ServoPin);

  myServo.write(0);
  delay(1000);
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
}


void loop() {
  temp = abs(dht.readTemperature());

  if(!isnan(temp)) {

    Serial.println("Measured a value\n(raw): " + String(temp));

    if(hasTemperatureChanged()) {
      int degree = calcServoMovement();
      myServo.write(degree);
    }
  }

  // Give DHT11 sensor some time to rest.
  delay(1000);
}
