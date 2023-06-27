# ArduinoRFIDwithOLED
This is the script or code for Arduino Nano (or any other device, just change minor necessary info) that connects an RFID (MFRC522 module) with a 4-pin I2C OLED display module. 

This code is able to:
- scan RFID card or fobs
- present UID, PICC type, and messages to the Serial Monitor
- present UID and messages to the connected OLED display
- validate a single user's UID / RFID to present an "UNLOCKED" message on OLED display

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/25423296/163456776-7f95b81a-f1ed-45f7-b7ab-8fa810d529fa.png">
  <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/25423296/163456779-a8556205-d0a5-45e2-ac17-42d089e3c3f8.png">
  <img alt="Shows a screenshot of Serial Monitor data at 9600 baud rate." src="https://user-images.githubusercontent.com/25423296/163456779-a8556205-d0a5-45e2-ac17-42d089e3c3f8.png">
</picture>
