# Duino Coin ESP Host WebConfig

<img src="img/Screen Shot 2022-01-03 at 23.10.54.png" alt="DuinoWebConfig" width="100%">

Currently Support ESP8266 (tested with Wemos D1 Mini).

Compatible out-of-the-box with installed slave miner from these repo:

https://github.com/ricaun/arduino-DuinoCoin <br> https://github.com/JK-Rolling/DuinoCoinI2C


# Instalation:
1. You must install and able to run one of those repo above (installation guide in their repo).
2. Add these library to your Arduino IDE :
   - https://github.com/esp8266/Arduino
   - https://github.com/bblanchon/ArduinoJson (v6)
   - https://github.com/tzapu/WiFiManager

# Disclaimer:
1. This is very early release version, hiccups, ups and down are expected.
2. There is no input validation in UI WebConfig.
3. I dont use external services for saving credential, completely local on your device.
4. I provide basic version, less pain in creating custom header, really. Easy to follow or modify (custom header and styling was not included in this repo). On success build, style will slightly different with attached screen.
5. Yes, you can modify or add functionality as your need.
6. There is no interrupt priority provided by manufacturers, it means sometimes reset button will fail. Press reset button multiple time will solve this.


# Usage:
1. Once BootUp there will be new AP "DuinoMinerConfig", just connect to it.
    - If your device is support Captive, There will be direct popup and fill up your config (Internet connection, Duino Coin, and optional custom mining pool)
    - If your device is not support Captive, do point 1 above, then goto browser type <b>192.168.4.1</b> as default address configuration, screen config will show up.
2. if Duino Coin Username is missing, there will not save any setting. No input validation yet.
3. Custom pool format IP:PORT (example 87.208.19.163:6006). No input validation yet.
4. Captive window will close in 30 Seconds after saving config, config via browser need close manually.
5. Auto Load Config, Auto mining after restart/power off, Auto recover Pool included.
6. AP "DuinoMinerConfig" only show if reset setting success or there is no saved config. Upon complete setting, it will mining in background as usual.
7. enjoy.

# Reset Button:
1. Connect your momentary push button GND to pin D5 (or any pin support external interrupt, adjust your code then).
2. After success reset settings AP "DuinoMinerConfig" will show once again.

# TODO:
1. Custom Styling
2. Add input validation
3. Add ESP32 Support
4. Optimize code
5. Custom header
6. and more ...
