# Duino Coin ESP Host WebConfig

Currently Support ESP8266 (tested Wemos D1 Mini). This is basic version, easy to follow or modify.

Compatible out-of-the-box with installed slave from this repo:

https://github.com/ricaun/arduino-DuinoCoin <br> https://github.com/JK-Rolling/DuinoCoinI2C


# Instalation:
1. You must install and able to run one of those repo above (instalation guide in their repo).
2. Add these library to your Arduino IDE :
  - https://github.com/esp8266/Arduino
  - https://github.com/bblanchon/ArduinoJson (v6)
  - https://github.com/tzapu/WiFiManager

# Disclaimer:
1. This is very early release version, hiccups, ups and down are expected.
2. There is no input validation in UI WebConfig
3. I dont use external services for saving credential, completely local on your device.

# Usage:
1. Once BootUp there will be new AP "DuinoMinerConfig", just connect to it.
    - If your device is support Captive, There will be direct popup and fill up your config (Internet connection, Duino Coin, and optional custom mining pool)
    - If your device is not support Captive, do point 1 above, the goto browser type 192.168.4.1 as default address configuration, screen config will show up.
2. if Duino Coin Username is missing, there will not save any setting. No input validation yet.
3. Custom pool format is like this 87.208.19.163:6006. No input validation yet.
4. Captive Window will close in 30 Second after saving config, config via browser need close manually.
5. Auto Load Config, Auto mining after restart/power off, Auto recover Pool included.
6. enjoy.

# TODO:
1. Custom Styling
2. Add input validation
3. Add ESP32 Support
4. Optimize code
5. and more ...
