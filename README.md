# 🔥 Smart Chimney System with GSM Alert

## 📌 Overview
An IoT-based Smart Chimney System that automatically controls fan speed based on temperature and humidity and detects gas/smoke leaks using MQ2 sensor. In emergency situations, it sends an SMS alert and makes an emergency call using GSM module.

---

## ⚙️ Components Used
- Arduino UNO
- DHT22 Temperature & Humidity Sensor
- MQ2 Gas Sensor
- SIM800L GSM Module
- 16x2 I2C LCD
- DC Motor + Motor Driver
- Buzzer
- Push Button

---

## 🚀 Features
- Automatic Mode (Temperature & Humidity Based)
- Manual Mode (Button Controlled)
- Gas Detection with Delay Confirmation
- SMS Alert System
- Emergency Call Function
- Real-time LCD Display

---

## 📸 Project Images

### Circuit Setup
![Circuit](images/pic%201.png)

### Hardware Setup
![Hardware](images/pic%202.png)

### Working Model
![Working](images/working%20model.png)

---

## 🧠 How It Works

- If temperature or humidity exceeds threshold → fan speed increases.
- If gas level exceeds safe limit for 3 seconds →  
  - Buzzer activates  
  - Fan runs at max speed  
  - SMS sent  
  - Emergency call made  

---

