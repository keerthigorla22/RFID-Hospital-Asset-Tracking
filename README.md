RFID-Hospital-Asset-Tracking

Hospital Asset Tracking Through IoT

Overview

This project proposes an IoT solution using RFID technology to track medical assets in real-time, enhancing hospital efficiency and patient care by reducing search time and improving resource allocation.

Features

Real-time medical equipment tracking

RFID-based unique identification and location tracking

Centralized data analysis system

Enhanced security and resource optimization

User-friendly web dashboard

Alerts for unauthorized access

Historical data logging for analytics

Installation

Clone the repository:

git clone https://github.com/username/hospital-asset-tracking.git

Navigate to the project directory:

cd hospital-asset-tracking

Install dependencies (if applicable):

npm install

Upload code to Arduino and ESP32 devices.

Run the backend server:

node server.js

Access the web dashboard at:

http://localhost:3000

Technologies Used

Hardware: Arduino Uno, ESP32, RFID Readers (MFRC522), LEDs, Buzzer, 16x2 LCD Display

Software Stack: Node.js, Express.js, MongoDB, HTML/CSS/JavaScript

Communication Protocols: SPI, I2C, and HTTP

Circuit Diagram
![img1](https://github.com/user-attachments/assets/0574993f-9943-4aad-879b-fb3676900fca)


Hardware Implementation

RFID Reader Code

Reads RFID tags and sends data to ESP32.

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

ESP32 Communication Code

Sends RFID data to the server.

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

Web Dashboard

Backend: Node.js and Express for API handling

Frontend: HTML, CSS, JavaScript for real-time data visualization

Database: MongoDB for storing asset data

Features:

Real-time asset location tracking

Alert system for unauthorized access

Analytics and reporting for hospital staff

Historical data tracking for analysis

Equipment Setup

Web Dashboard Interface

Testing and Results

Unit Testing: Verify individual components like RFID readers and ESP32.

Integration Testing: Ensure smooth data flow between hardware and the server.

Performance Evaluation: Assess accuracy, response time, and data latency.

Contributing

Fork the repository.

Create a new branch:

git checkout -b feature-name

Commit changes:

git commit -m "Add feature"

Push to the branch:

git push origin feature-name

Open a pull request.

Contact

For any inquiries, reach out to gorlakeerthi2205@gmail.com.


