//Written by Nick Koumaris
//edits by @TechWithRita

/*
 *        ** PINOUT FOR ARDUINO NANO, 128X64 OLED I2C, RFID-RC522  <<>>  SUPER DUPER EASY SETUP!!! **
 *        
 *   RFID-RC522: SDA --> ARDUINO NANO D10                           |   OLED: SDA --> ARDUINO NANO A4 
 *               SCK --> ARDUINO NANO D13                           |         SCL --> A.N. A5
 *               MOSI --> (A.N, you get the point) D11              |         VCC --> 5V BREADBOARD / ARDUINO NANO SOURCED 5V OUTPUT PIN
 *               MISO --> D12                                       |         GND --> GROUND OR NEGATIVE TERMINAL ON BREADBOARD
 *               IRQ --> NOT USED                                   |
 *               GND --> GROUND OR NEGATIVE TERMINAL ON BREADBOARD  |
 *               RST --> D9
 *               3.3V --> 3V3 PIN ON ARDUINO (NOT THE BREADBOARD'S 5V SOURCE, THAT'S FOR THE OLED DISPLAY ONLY)
*/

#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
#define SS_PIN 10
#define RST_PIN 9
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
int code[] = {48,13,137,34}; //This is the stored UID
int codeRead = 0;
String uidString;
void setup() {
  
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (if 0x3C doesn't work) ... (both 128*64 AND 128*32 can have either code address)
  displayMainGraphic();
}

//continuous loop to read RFID without pauses or stops (causes antenna to continuosly seek new codes)
void loop() {
  if(  rfid.PICC_IsNewCardPresent())
  {
      readRFID();
  }
  delay(100);
}

/* 
 *  <<< Functions are listed below this mark >>>
*/

// This Display Main Graphic function displays "SCAN RFID" on the OLED screen
// it is not responsible for putting "UNLOCKED" on screen, see printUnlockMessage() below

void displayMainGraphic(){
  // Clear the buffer.
  display.clearDisplay();
  display.display();  // sends information to the board, (pushes data currently in RAM to SSD1306 display) for ref. see: -http://adafruit.github.io/Adafruit_SSD1306/html/class_adafruit___s_s_d1306.html#a650aa88a18f2d6a5c2d5442602d12286)
  display.setTextColor(WHITE); // or BLACK);
  display.setTextSize(2);
  display.setCursor(10,0); 
  display.print("SCAN RFID");
  display.display(); 
}

//this function reads the data on each card regardless if it's accepted or not, and displays retained info onto the serial monitor
//  ***adjust serial monitor's data / baud rate to 9600 if random characters or partial data is presented***
void readRFID()
{
  
  rfid.PICC_ReadCardSerial();
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
    clearUID();
   // prints to serial monitor
    Serial.println("Scanned PICC's UID:");
    printDec(rfid.uid.uidByte, rfid.uid.size);
    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    
    printUID();
    int i = 0;
    boolean match = true;
    while(i<rfid.uid.size)
    {
      if(!(rfid.uid.uidByte[i] == code[i]))
      {
           match = false;
      }
      i++;
    }
    if(match)
    {
      Serial.println("\nI know this card!");
      printUnlockMessage();
    }else
    {
      Serial.println("\nUnknown Card");
      displayMainGraphic();
      
    }
    // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
  void clearUID()
  {
    display.setTextColor(BLACK); // or BLACK);
    display.setTextSize(1);
    display.setCursor(30,20); 
    display.print(uidString);
    display.display();
  }
  
  //prints card's UID to OLED display
  void printUID()
  {
    display.setTextColor(WHITE); // or BLACK);
    display.setTextSize(1);
    display.setCursor(0,20); 
    display.print("UID: ");
    display.setCursor(30,20); 
    display.print(uidString);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.display();
  }

  // this function is responsible for putting "UNLOCKED" on OLED display breifly, then returning to original function
  // to display main graphic / message of "SCAN RFID" see "displayMainGraphic()" above
  void printUnlockMessage()
  {
    display.display();
    display.setTextColor(WHITE); // or BLACK);
    display.setTextSize(2);
    display.setCursor(10,0); 
    display.print("Unlocked");
    display.display();
    delay(2000);
    
    displayMainGraphic(); // returns to the function above to present message, "SCAN RFID" 
  }
