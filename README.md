# RFID-Hospital-Asset-Tracking
# Hospital Asset Tracking Through IoT

## Overview
This project proposes an IoT solution using RFID technology to track medical assets in real-time, enhancing hospital efficiency and patient care by reducing search time and improving resource allocation.

## Features
- Real-time medical equipment tracking
- RFID-based identification and location tracking
- Centralized data analysis system
- Enhanced security and resource optimization

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/username/hospital-asset-tracking.git
   ```
2. Navigate to the project directory:
   ```bash
   cd hospital-asset-tracking
   ```
3. Install dependencies (if applicable):
   ```bash
   npm install
   ```
4. Upload code to Arduino and ESP32 devices.

## Technologies Used
- Arduino Uno
- ESP32
- RFID Readers (MFRC522)
- LEDs and Buzzer
- 16x2 LCD Display
- Node.js and Express
- MongoDB

## Circuit Diagram
![Circuit Diagram](images/circuit_diagram.png)

## Code Snippets
### RFID Reader Code
```cpp
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN_1 10

MFRC522 rfid1(SS_PIN_1, RST_PIN);

void setup() {
  SPI.begin();
  rfid1.PCD_Init();
  Serial.begin(115200);
}

void loop() {
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    Serial.print("RFID Tag detected: ");
    for (byte i = 0; i < rfid1.uid.size; i++) {
      Serial.print(rfid1.uid.uidByte[i], HEX);
    }
    Serial.println();
    rfid1.PICC_HaltA();
  }
}
```

### ESP32 Communication Code
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
const char* serverUrl = "http://yourserver.com/updateAsset";

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int response = http.POST("{\"data\":\"" + data + "\"}");
    http.end();
  }
}
```

## Web Dashboard
- Backend: Node.js and Express
- Frontend: HTML/CSS/JavaScript
- MongoDB for data storage

## Equipment Setup
![Equipment Setup](images/equipment_setup.png)

## Web Dashboard Interface
![Web Dashboard](images/web_dashboard.png)

## Contributing
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit changes:
   ```bash
   git commit -m "Add feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

## License
[Specify the license, e.g., MIT, Apache, etc.]

## Contact
For any inquiries, reach out to [Your Email] or [Your Social Media Handle].

