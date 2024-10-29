#define StartButtonPin 18
#define StopButtonPin 3
#define ResetButtonPin 2

#include <Arduino.h>

enum TimerState {
    On,
    Off,
};

volatile TimerState timerstate = Off;
volatile uint16_t timerValue = 0; 

const unsigned long debounceDelay = 200;
volatile unsigned long lastStartPress = 0;
volatile unsigned long lastStopPress = 0;
volatile unsigned long lastResetPress = 0;


void changeState(TimerState newState) {
  if(timerstate != newState) {
    timerstate = newState;
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
    changeState(On);
  }
}


void stopButtonReleased() {
  if (debounce(lastStopPress)) {
    Serial.println("Stop Button was pressed!");
    changeState(Off);
  }
}


void resetButtonReleased() {
  if (debounce(lastResetPress)) {
    Serial.println("Reset Button was pressed!");
    timerValue = 0;
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
}


void loop() {
  
  

}