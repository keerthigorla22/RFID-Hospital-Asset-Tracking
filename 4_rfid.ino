#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9

#define SS_PIN1 10
#define SS_PIN2 8
#define SS_PIN3 7
#define SS_PIN4 6

MFRC522 mfrc522_1(SS_PIN1, RST_PIN);   // Create MFRC522 instance for RFID1
MFRC522 mfrc522_2(SS_PIN2, RST_PIN);   // Create MFRC522 instance for RFID2
MFRC522 mfrc522_3(SS_PIN3, RST_PIN);   // Create MFRC522 instance for RFID3
MFRC522 mfrc522_4(SS_PIN4, RST_PIN);   // Create MFRC522 instance for RFID4

// Predefined UIDs
byte UID1[] = {0xC3, 0x38, 0x5E, 0x27};
byte UID2[] = {0xA3, 0x6F, 0x32, 0x27};
byte UID3[] = {0xD3, 0x12, 0x1A, 0x29};
byte UID4[] = {0x33, 0xD1, 0xB4, 0x29};
byte UID5[] = {0xA3, 0x74, 0x72, 0x13};
byte UID6[] = {0xE3, 0xA8, 0x46, 0x14};
byte UID7[] = {0x63, 0x72, 0x75, 0x13};
byte UID8[] = {0xB3, 0xCE, 0x58, 0x14};

// Corresponding names
const char* names[] = {
  "Sai",
  "Keerthi",
  "Sujith",
  "Tejaswini",
  "ventilator",
  "pulsometry",
  "BP monitor",
  "CT Scan"
};

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus

  mfrc522_1.PCD_Init(); // Init RFID1
  mfrc522_2.PCD_Init(); // Init RFID2
  mfrc522_3.PCD_Init(); // Init RFID3
  mfrc522_4.PCD_Init(); // Init RFID4
}

void loop() {
  checkRFID(mfrc522_1, "Room 1");
  checkRFID(mfrc522_2, "Room 2");
  checkRFID(mfrc522_3, "Saferoom");
  checkRFID(mfrc522_4, "Exit");
  delay(1000); // Add a delay to avoid flooding the serial output
}

void checkRFID(MFRC522 &mfrc522, String roomName) {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  int nameIndex = getNameIndex(mfrc522.uid.uidByte, mfrc522.uid.size);
  if (nameIndex != -1) {
    Serial.print(roomName);
    Serial.print(" detected ");
    Serial.println(names[nameIndex]);
  } else {
    Serial.print(roomName);
    Serial.println(" detected an unknown card.");
  }
  mfrc522.PICC_HaltA();
}

int getNameIndex(byte *uid, byte uidSize) {
  byte* uids[] = {UID1, UID2, UID3, UID4, UID5, UID6, UID7, UID8};
  int numUIDs = sizeof(uids) / sizeof(uids[0]);

  for (int i = 0; i < numUIDs; i++) {
    if (uidSize == 4 && compareUID(uid, uids[i])) {
      return i;
    }
  }
  return -1;
}

bool compareUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}