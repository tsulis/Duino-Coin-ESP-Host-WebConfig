/*
 
  DuinoWebConfig added by Triyatno Sulis
  
*/

void SetupWifi() {

    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("\n Starting");
    pinMode(resetButtonPin, INPUT_PULLUP);

    // If you uncomment this command, you will always lost settings after restart, back to setup mode.
    // wm.resetSettings();

    int customFieldLength = 40;
    new(&c_duco_user_field) WiFiManagerParameter("c_duco_userId", "DUINO MINER ID", "", customFieldLength,
                                                 "placeholder=\"Your DuinoCoin ID\" type=\"textbox\"");

    new(&c_duco_custom_pool) WiFiManagerParameter("c_duco_manual_pool", "Your Favourite Pool (optional)", "",
                                                  customFieldLength,
                                                  "placeholder=\"50.112.145.154:6000\" type=\"textbox\"");
    wm.addParameter(&c_duco_user_field);
    wm.addParameter(&c_duco_custom_pool);
    wm.setSaveParamsCallback(saveParamCallback);
    std::vector<const char *> menu = {"wifi", "exit"};
    wm.setMenu(menu);
    wm.setClass("invert");
    wm.setConfigPortalTimeout(30);

    bool res;
    res = wm.autoConnect("DuinoMinerConfig");

    if (!res) {
        Serial.println("Failed to connect or hit timeout");
        ESP.restart();
    } else {
        Serial.println("connected...BAAMM! :)");
        loadConfig();
        Serial.println("ducoUser : " + ducouser);
        Serial.println("host : " + host);
        Serial.println("port : " + String(port));
    }
}

bool loadConfig() {
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return false;
    }

    StaticJsonDocument<200> doc;
    auto error = deserializeJson(doc, configFile);
    if (error) {
        Serial.println("Failed to parse config file");
        return false;
    }

    String localGetDucoUsername = doc["ducouser"];
    ducouser = localGetDucoUsername;

    String localGetUserPool = doc["host"];
    host = localGetUserPool;

    int localGetUserPort = doc["port"];
    port = localGetUserPort;

    Serial.println("Loaded setDucoUserName: " + ducouser);
    Serial.println("Loaded setDucoUserPool: " + host);
    Serial.println("Loaded setDucoUserPort: " + String(port));

    return true;
}

bool saveConfig() {
    StaticJsonDocument<200> doc;
    doc["ducouser"] = ducouser;
    doc["host"] = host;
    doc["port"] = port;

    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
        return false;
    }

    serializeJson(doc, configFile);
    return true;
}

String setParseManualPool(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void resetCreds() {
    // ugly cheat reset settings, sometimes settings still reside after resetSettings() called for once, a glitch in WiFiManager lib?
    for (int i = 0; i < 6; i++) {
        delay(100);
        wm.resetSettings();
        blink(BLINK_SETUP_COMPLETE);
    }

    ducouser = "";
    host = "";
    port = 0;
    saveConfig();
    ESP.restart();
}

void keyPress() {
    resetCreds();
    KeyPressCount++;
    Serial.println("keyPress");
}

String getParam(String name) {
    String value;
    if (wm.server->hasArg(name)) {
        value = wm.server->arg(name);
    }
    return value;
}

void saveParamCallback() {

    ducouser = getParam("c_duco_userId");
    ducoUserPool = getParam("c_duco_manual_pool");
    ducoUserPool.trim();
    
    bool checkUser = (ducouser == "" || ducouser == NULL) ? true : false;
    bool checkManualPool = (ducoUserPool == "" || ducoUserPool == NULL) ? true : false;

    //todo: sanitize if input invalid, better in UI
    //atm, there is no format validation yet. Full gas no brakes. :D
    if (!checkManualPool) {
        host = setParseManualPool(ducoUserPool, ':', 0);
        port = (setParseManualPool(ducoUserPool, ':', 1)).toInt();
    }

    saveConfig();

    //todo: handle input validation in UI instead here. Avoid saving empty duco username
    if (checkUser) {
        resetCreds();
    }
}

#if ESP8266
ICACHE_RAM_ATTR void resetWifiSetting() {

    if (millis() - keyPrevMillis >= keySampleIntervalMs) {
        keyPrevMillis = millis();

        byte currKeyState = digitalRead(resetButtonPin);

        // quick cheat, please retouch as you wish.
        if (currKeyState == (currKeyState == LOW) ? HIGH : HIGH) {
            keyPress();
        }
    }
}
#endif
