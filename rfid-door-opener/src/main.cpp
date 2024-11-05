#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 16
#define LED_GREEN 12
#define LED_RED 14
#define BUZZER 2
#define LED_ON_DELAY 1000


MFRC522 mfrc522(SS_PIN, RST_PIN);
const char* cardUID = "CC E9 DF 37";


void blinkLED(const uint8_t ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(LED_ON_DELAY);
  digitalWrite(ledPin, LOW);
}


String getCardContent() {
  String content= "";
  for(byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  return content;
}


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  noTone(BUZZER);

  Serial.println("Put your card to the reader...");
}


void loop() {
  // Look for new cards and select one of the cards.
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String cardContent = getCardContent();
  Serial.println("UID tag : " + cardContent);

  if(cardContent.substring(1) == cardUID) {
    Serial.println("---\nAuthorized access\n---");
    tone(BUZZER, 800, LED_ON_DELAY);
    blinkLED(LED_GREEN);
  } else {
    Serial.println("---\nAccess denied\n---");
    tone(BUZZER, 300, LED_ON_DELAY);
    blinkLED(LED_RED);
  }
}