/*
  DoinoCoin_Esp_Master.ino
  created 10 05 2021
  by Luiz H. Cassettari

  DuinoWebConfig added by Triyatno Sulis

  
*/

// You will need install library
// 1. https://github.com/esp8266/Arduino
// 2. https://github.com/bblanchon/ArduinoJson
// 3. https://github.com/tzapu/WiFiManager

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h> // V6!
#include <WiFiManager.h>
#include <StreamString.h>

#define BLINK_SHARE_FOUND    1
#define BLINK_SETUP_COMPLETE 2
#define BLINK_CLIENT_CONNECT 3
#define BLINK_RESET_DEVICE   5


#if ESP8266
#define LED_BUILTIN 2
#define MINER "AVR I2C v2.75"
#define JOB "AVR"
#define resetButtonPin D5 // pin definition for reset button (momentary push button)
#endif

void wire_setup();
void wire_readAll();
boolean wire_exists(byte address);
void wire_sendJob(byte address, String lastblockhash, String newblockhash, int difficulty);
void Wire_sendln(byte address, String message);
void Wire_send(byte address, String message);
String wire_readLine(int address);
boolean wire_runEvery(unsigned long interval);

unsigned long keyPrevMillis = 0;
const unsigned long keySampleIntervalMs = 200;
byte KeyPressCount = 0;
String ducouser = "";
String ducoUserPool = "";

// change as you wish as default pool
String host = "87.208.19.163";
int port = 6006;

const char *rigIdentifier = "AVR";

WiFiManager wm;
WiFiManagerParameter c_duco_user_field, c_duco_custom_pool;

void handleSystemEvents(void) {
    yield();
}

void blink(uint8_t count, uint8_t pin = LED_BUILTIN) {
    uint8_t state = HIGH;
    for (int x = 0; x < (count << 1); ++x) {
        digitalWrite(pin, state ^= HIGH);
        delay(50);
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.print("\nDuino-Coin");
    Serial.println(MINER);

    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    wire_setup();
    SetupWifi();

    blink(BLINK_SETUP_COMPLETE);

    attachInterrupt(digitalPinToInterrupt(resetButtonPin), resetWifiSetting, CHANGE);

    if (!loadConfig()) {
        Serial.println("Failed to load config");
    } else {
        Serial.println("Config loaded");
    }
}

void loop() {
    clients_loop();
}
