#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);

// Define the hardcoded UIDs and corresponding names
byte UID1[] = {0xC3, 0x38, 0x5E, 0x27};
byte UID2[] = {0xA3, 0x6F, 0x32, 0x27};
byte UID3[] = {0xD3, 0x12, 0x1A, 0x29};
byte UID4[] = {0x33, 0xD1, 0xB4, 0x29};
byte UID5[] = {0xA3, 0x74, 0x72, 0x13};
byte UID6[] = {0xE3, 0xA8, 0x46, 0x14};
byte UID7[] = {0x63, 0x72, 0x75, 0x13};
byte UID8[] = {0xB3, 0xCE, 0x58, 0x14};


const char* name1 = "Sai";
const char* name2 = "Keerthi";
const char* name3 = "Sujith";
const char* name4 = "Tejaswini";
const char* name5 = "ventilater";
const char* name6 = "pulsometry";
const char* name7 = "BP monitor";
const char* name8 = "CT Scan";


void setup() {
  Serial.begin(9600);
  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522
  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {  // new tag is available
    if (rfid.PICC_ReadCardSerial()) {  // NUID has been read
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      if (compareUIDs(rfid.uid.uidByte, UID1)) {
        Serial.print("Name: ");
        Serial.println(name1);
      } else if (compareUIDs(rfid.uid.uidByte, UID2)) {
        Serial.print("Name: ");
        Serial.println(name2);
      } else if (compareUIDs(rfid.uid.uidByte, UID3)) {
        Serial.print("Name: ");
        Serial.println(name3);
      } else if (compareUIDs(rfid.uid.uidByte, UID4)) {
        Serial.print("Name: ");
        Serial.println(name4);
      } else if (compareUIDs(rfid.uid.uidByte, UID5)) {
        Serial.print("Name: ");
        Serial.println(name5);
      } else if (compareUIDs(rfid.uid.uidByte, UID6)) {
        Serial.print("Name: ");
        Serial.println(name6);
      } else if (compareUIDs(rfid.uid.uidByte, UID7)) {
        Serial.print("Name: ");
        Serial.println(name7);
      } else if (compareUIDs(rfid.uid.uidByte, UID8)) {
        Serial.print("Name: ");
        Serial.println(name8);  
      } else {
        Serial.println("Unknown Product");
      }

      rfid.PICC_HaltA();       // halt PICC
      rfid.PCD_StopCrypto1();  // stop encryption on PCD

      delay(2000);  // Wait for 2 seconds before next scan
    }
  }
}

// Function to compare two UIDs
bool compareUIDs(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
