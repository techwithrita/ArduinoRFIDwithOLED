# ArduinoRFIDwithOLED
This is the script or code for Arduino Nano (or any other device, just change minor necessary info) that connects an RFID (MFRC522 module) with a 4-pin I2C OLED display module. 

**This code is able to:**
- scan RFID card or fobs
- present UID, PICC type, and messages to the Serial Monitor
- present UID and messages to the connected OLED display
- validate a single user's UID / RFID to present an "UNLOCKED" message on OLED display

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/rhitalin/ArduinoRFIDwithOLED/blob/main/screenCaptureRFIDOLED.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/rhitalin/ArduinoRFIDwithOLED/blob/main/screenCaptureRFIDOLED.png">
  <img alt="Shows a screenshot of Serial Monitor data at 9600 baud rate." src="https://github.com/rhitalin/ArduinoRFIDwithOLED/blob/main/screenCaptureRFIDOLED.png)https://github.com/rhitalin/ArduinoRFIDwithOLED/blob/main/screenCaptureRFIDOLED.png">
</picture>

**Here is how the devices are connected / wired:**
<picture>
<img alt="Shows an RFID antenna connected to an OLED display and an Arduino Nano" src="https://github.com/rhitalin/ArduinoRFIDwithOLED/blob/main/ArduinoNanoRFIDandOLED.jpg">
</picture>
