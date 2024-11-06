#include <Arduino.h>
#include <Servo.h>


#define TRIG_PIN D0
#define ECHO_PIN D5
#define POT_PIN A0
#define SERVO_PIN D2


Servo myServo;
const float speedOfSound = 0.0343f; // In centimeter/second


void sendSoundPulse() {
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
}


long measureDistance() {
  sendSoundPulse();

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (float(duration) * speedOfSound) / 2.0f;
  
  return distance;
}


void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  myServo.attach(SERVO_PIN);
}


void loop() {
  int potValue = analogRead(POT_PIN);

  int angle = map(potValue, 0, 1023, 0, 180);
  myServo.write(angle);

  long distance = measureDistance();

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" degrees, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Small delay for smoother output
}