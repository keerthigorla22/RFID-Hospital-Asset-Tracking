# RFID-Hospital-Asset-Tracking

# Hospital Asset Tracking Through IoT

## Overview
This project aims to enhance hospital efficiency and patient care through real-time tracking of medical assets using IoT and RFID technology. By minimizing search time and improving resource allocation, the system ensures optimal equipment management.

## Objectives
- Reduce the time spent locating medical assets
- Prevent loss or theft of equipment
- Improve hospital workflow and resource allocation
- Provide real-time analytics and historical data logging

## Features
- Real-time medical asset tracking
- RFID-based unique identification and location tracking
- Centralized data analysis system
- Enhanced security and theft prevention
- User-friendly web dashboard
- Alert notifications for unauthorized access
- Historical data tracking for performance evaluation
- Scalability for future integration with other hospital management systems

## Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/username/hospital-asset-tracking.git
   ```
2. **Navigate to the project directory:**
   ```bash
   cd hospital-asset-tracking
   ```
3. **Install dependencies:**
   ```bash
   npm install
   ```
4. **Upload code to Arduino and ESP32 devices.**
5. **Run the backend server:**
   ```bash
   node server.js
   ```
6. **Access the web dashboard:**
   ```
   http://localhost:3000
   ```

## Technologies Used
- **Hardware:** Arduino Uno, ESP32, RFID Readers (MFRC522), LEDs, Buzzer, 16x2 LCD Display
- **Software Stack:** Node.js, Express.js, MongoDB, HTML/CSS/JavaScript
- **Communication Protocols:** SPI, I2C, and HTTP
- **Cloud Platform (Optional):** AWS or Google Cloud for scalability

## System Architecture
1. **RFID Readers:** Identify and transmit asset information.
2. **Arduino Uno:** Controls the RFID readers and sends data to ESP32.
3. **ESP32:** Connects to the server over Wi-Fi and sends the data.
4. **Node.js Backend:** Handles API requests and stores data in MongoDB.
5. **MongoDB Database:** Stores asset data and logs.
6. **Web Dashboard:** Visualizes asset location and provides analytics.

## Circuit Diagram
<img src="https://github.com/user-attachments/assets/21b77a5b-a06d-473a-b171-4fd74cab094b" width="400">
<img src="https://github.com/user-attachments/assets/4ff5f4e8-6325-4f50-94ac-237a837f2983" width="400">

## Hardware Implementation
### RFID Reader Code
Reads RFID tags and sends data to ESP32.
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
Sends RFID data to the server.
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
- **Backend:** Node.js and Express for API handling
- **Frontend:** HTML, CSS, JavaScript for real-time data visualization
- **Database:** MongoDB for storing asset data

### Dashboard Features
- Real-time asset location tracking
- Alert notifications for unauthorized access
- Analytics and reporting
- Historical data tracking for performance evaluation
- User management and access control

## Testing and Results
1. **Unit Testing:** Verify the functionality of RFID readers, Arduino, and ESP32.
2. **Integration Testing:** Ensure smooth communication between hardware and server.
3. **Performance Testing:** Assess response time, accuracy, and data latency.
4. **Security Testing:** Evaluate the system's vulnerability to unauthorized access.

## Future Enhancements
- Integration with hospital management systems
- Predictive analytics for equipment maintenance
- Cloud-based data storage for scalability
- Enhanced security protocols

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

## Contact
For any inquiries, reach out to gorlakeerthi2205@gmail.com.

