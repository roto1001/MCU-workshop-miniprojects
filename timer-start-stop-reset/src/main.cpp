/*
 * Project: timer-start-stop-reset
 * 
 * Author: Robert Tomor
 * Date Created: 6.11.2024
 * Last Modified: 13.11.2024
 * 
 * License: MIT License
 * 
 * Copyright (c) 2024 Robert Tomor
*/


#define StartButtonPin 18
#define StopButtonPin 3
#define ResetButtonPin 2

#define Dig_D1 32
#define Dig_D2 33
#define Dig_D3 36
#define Dig_D4 40

#define Seg_A 34
#define Seg_B 37
#define Seg_C 43
#define Seg_D 44
#define Seg_E 42
#define Seg_F 35
#define Seg_G 41
#define Seg_DP 45

#include <Arduino.h>
#include <SevSeg.h>

volatile bool timerRunning = false;
volatile uint16_t timerValue = 0; 

const unsigned long debounceDelay = 200;
volatile unsigned long lastStartPress = 0;
volatile unsigned long lastStopPress = 0;
volatile unsigned long lastResetPress = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const unsigned long interval = 1000;

SevSeg sevseg;


bool checkInterval() {
  if((currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}


void updateDisplay(uint16_t value) {
  char buffer[10];
  itoa(value, buffer, 10);
  sevseg.setChars(buffer);
  sevseg.refreshDisplay();
}


void changeTimerRunningState(bool newTimerState) {
  if(timerRunning != newTimerState) {
    timerRunning = newTimerState;
  }
}


bool debounce(volatile unsigned long &lastPressTime) {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime >= debounceDelay) {
        lastPressTime = currentTime;
        return true;
    }
    return false;
}


void startButtonReleased() {
  if (debounce(lastStartPress)) {
    Serial.println("Start Button was pressed!");
    changeTimerRunningState(true);
  }
}


void stopButtonReleased() {
  if (debounce(lastStopPress)) {
    Serial.println("Stop Button was pressed!");
    changeTimerRunningState(false);
  }
}


void resetButtonReleased() {
  if (debounce(lastResetPress)) {
    Serial.println("Reset Button was pressed!");
    timerValue = 0;
    updateDisplay(timerValue);
  }
}


void setupButtonInterrupt(void (*func)(), uint8_t inputPin) {
  pinMode(inputPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(inputPin),
                  func,
                  FALLING);
}


void setup() {
  Serial.begin(9600);

  // Initialize the buttons
  setupButtonInterrupt(startButtonReleased, StartButtonPin);
  setupButtonInterrupt(stopButtonReleased, StopButtonPin);
  setupButtonInterrupt(resetButtonReleased, ResetButtonPin);

  const uint8_t numDigits = 4;  
  const bool resistorsOnSegments = 0; 
  // Define the input pins for the 7-segment display segments.
  const uint8_t segmentPins[] = {Seg_A, Seg_B, Seg_C, Seg_D, Seg_E, Seg_F, Seg_G, Seg_DP};
  // Define the input pins for the 7-segment display digits.
  const uint8_t digitPins[] = {Dig_D1, Dig_D2, Dig_D3, Dig_D4};

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(60);

  sevseg.setChars("8888");
}


void loop() {
  currentMillis = millis();

  if(timerRunning) {
    if(checkInterval()) {
      timerValue += 1;
      updateDisplay(timerValue);
    }
  } else {
    previousMillis = currentMillis;
  }

  sevseg.refreshDisplay();
}