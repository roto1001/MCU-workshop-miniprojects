#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 

// SD card settings
#define CS_PIN 10
#define SPI_SPEED SD_SCK_MHZ(4)


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SdFat sdcard;
JsonDocument configData;


void initializeDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }
  
  display.clearDisplay();
  display.display();
}


void initializeFiles() {
  if (!sdcard.exists("/config.json")) {
    FsFile config = sdcard.open("/config.json", FILE_WRITE);

    if (!config) {
        Serial.println("config file could not be created");
        return;
    }
    config.println(R"({"ssid":"","password":""})");
    config.close();
  }
}


void initializeSdCard() {
  if (!sdcard.begin(CS, SPI_SPEED)) {
    Serial.println("SD initialization failed.");
    return;
  }

  initializeFiles();
}


bool loadConfigData() {
  FsFile wifiCredentialsFile = sdcard.open("/config.json", FILE_READ);

  if (!wifiCredentialsFile) {
    Serial.println("Config file could not be read.");
    return false;
  }

  String fileContent = wifiCredentialsFile.readString();
  wifiCredentialsFile.close();

  DeserializationError error = deserializeJson(configData, fileContent);

  if (error) {
    Serial.print(F("Failed to parse JSON: "));
    Serial.println(error.f_str());
    return false;
  }

  return true;
}


void saveConfigData() {
  FsFile configFile = sdcard.open("/config.json", FILE_WRITE | O_TRUNC);

  if (!configFile) {
    Serial.println("Config file could not be opened for writing.");
    return;
  }

  serializeJson(configData, configFile);
  configFile.close();
}


void displayCredentialsForm() {
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("SSID:");
  display.setCursor(0, 10);
  display.print("Password:");

  display.display();
}


void updateCredentials(const char* ssid, const char* password) {
  display.fillRect(59, 0, 40, 61 , BLACK);

  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(60, 0);
  display.print(ssid);
  display.setCursor(60, 10);
  display.print(password);

  display.display();
}


void populateDisplayData() {
  const char* ssid = configData["ssid"];
  const char* password = configData["password"];
  updateCredentials(ssid, password);
}


void promptUserForInput() {
  Serial.println("Select an option:");
  Serial.println("1 - Set SSID");
  Serial.println("2 - Set Password");
  Serial.println("3 - Show Credentials");
}


String cleanSerialInput() {
  String input = Serial.readStringUntil('\n');
  input.trim();
  return input;
}


String getDataFromSerialInput() {
  while (!Serial.available()); // BLOCKING OPERATION
  return cleanSerialInput();
}


void setup() {
  Serial.begin(9600);
  while (!Serial){};
  Serial.println("Serial connection established.");

  initializeDisplay();
  initializeSdCard();

  if (!loadConfigData()) {
    Serial.println("Failed to load config data.");
    return;
  }

  displayCredentialsForm();
  populateDisplayData();
  promptUserForInput();
}


void loop() {
  if (Serial.available() > 0) {
    String input = cleanSerialInput(); 

    if (input == "1") {
      Serial.println("Enter new SSID:");
      String ssid = getDataFromSerialInput(); 
      
      configData["ssid"] = ssid;

      saveConfigData();
      populateDisplayData();
    }
    else if (input == "2") {
      Serial.println("Enter new Password:");
      String password = getDataFromSerialInput();

      configData["password"] = password;

      saveConfigData();
      populateDisplayData();
    }
    else if (input == "3") {
      Serial.print("SSID: ");
      Serial.println(configData["ssid"].as<const char*>());

      Serial.print("Password: ");
      Serial.println(configData["password"].as<const char*>());

      populateDisplayData();
    }
    else {
      Serial.println("Invalid option. Please select 1, 2, or 3.");
    }

    promptUserForInput();
  }
}
