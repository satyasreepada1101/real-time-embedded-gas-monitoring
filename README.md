# 🔥 Real-Time Embedded Gas Monitoring & Ventilation System

## 📌 Overview
This project implements a real-time embedded gas monitoring and automated ventilation system using Arduino and Embedded C.

The system continuously monitors temperature, humidity, and gas/smoke concentration in a kitchen environment. Based on sensor readings, it dynamically adjusts ventilation speed. In hazardous situations, it activates an alarm and sends remote alerts using a GSM module.

## 🏗 System Architecture

### Input Layer
- DHT22 – Temperature & Humidity sensing
- MQ-2 – Gas/Smoke detection
- Push Button – Manual override control

### Processing Layer
- Arduino Uno (ATmega328P)
- Threshold evaluation logic
- Non-blocking timing using `millis()`
- Multi-mode control (Auto / Manual / Emergency)

### Output Layer
- 12V DC Fan (PWM controlled via L298N driver)
- Passive Buzzer (audio alert)
- 16x2 I2C LCD (real-time system display)
- SIM800L GSM module (SMS + Call alert)

## 🚀 Key Features

- Automatic fan speed control based on temperature & humidity thresholds
- Gas detection with confirmation delay to reduce false triggers
- Emergency mode with:
  - Buzzer activation
  - Maximum fan speed
  - SMS alert
  - Automated phone call
- Manual override with multi-speed selection
- Real-time system feedback via LCD
- Modular Embedded C design with dedicated functional units

## 🧠 Core Logic Implementation

- Gas detection uses analog threshold monitoring with timed confirmation logic.
- Auto mode calculates required fan speed using dominant environmental parameter.
- Manual mode cycles through speed levels using button debouncing.
- Safety logic overrides all other operations when gas is detected.

## ⚙️ Technologies Used

- Embedded C
- Arduino IDE
- Sensor Integration
- PWM Motor Control
- AT Command Communication (GSM)
- I2C Communication
- Serial Debugging

## 🛠 Hardware Setup

### Components Required
- Arduino Uno
- DHT22 Temperature & Humidity Sensor
- MQ-2 Gas Sensor
- SIM800L GSM Module
- L298N Motor Driver
- 12V DC Fan
- 16x2 I2C LCD Display
- Passive Buzzer
- Push Button
- 12V Adapter (for fan)
- 5V Supply / USB (for Arduino)
- 3.7V Li-ion Battery (for SIM800L)

### Basic Connections

- DHT22 → Digital Pin 2
- MQ-2 → Analog Pin A0
- Fan Driver ENA → Pin 9 (PWM)
- Fan Driver IN1 → Pin 4
- Fan Driver IN2 → Pin 5
- Buzzer → Pin 10
- Push Button → Pin 3 (INPUT_PULLUP)
- GSM RX/TX → Pins 7 & 8 (SoftwareSerial)
- LCD → I2C (SDA, SCL)

Ensure all components share a common ground.

## 💻 Software Setup

### 1️⃣ Install Arduino IDE
Download from: https://www.arduino.cc/en/software

### 2️⃣ Install Required Libraries
In Arduino IDE → Sketch → Manage Libraries:

Install:
- DHT Sensor Library (Adafruit)
- LiquidCrystal_I2C
- Wire (default)
- SoftwareSerial (default)

### 3️⃣ Upload the Code

1. Open `smart_chimney.ino`
2. Select Board: Arduino Uno
3. Select correct COM Port
4. Click Upload

## 📱 GSM Configuration

Before uploading, edit this line inside the code:

```cpp
String phoneNumber = "+91XXXXXXXXXX";
```

Replace with your own phone number.

Insert a valid 2G-enabled SIM card into SIM800L.

Ensure proper external power supply for GSM module (it requires high current during transmission).

## ⚠️ Important Notes

- MQ-2 sensor requires initial warm-up (~30–60 seconds).
- SIM800L works only with 2G networks.
- Ensure stable power supply to avoid GSM reset issues.
- Threshold values can be adjusted in the `calculateRequiredSpeed()` function.

## 🧪 Testing Procedure

1. Power ON the system.
2. Wait for sensor stabilization.
3. Introduce smoke near MQ-2 sensor.
4. After confirmation delay:
   - Buzzer activates
   - Fan runs at maximum speed
   - SMS is received
   - Call is initiated

## 📸 Project Images

### Circuit Setup
![Circuit](images/pic%201.png)

### Hardware Setup
![Hardware](images/pic%202.png)

### Working Model
![Working](images/working%20model.png)

## 📂 Repository Structure

```
real-time-embedded-gas-monitoring/
│
├── code/
│   └── smart_chimney.ino
│
├── images/
│   ├── pic 1.png
│   ├── pic 2.png
│   └── working model.png
│
└── README.md
```

## 🎯 Purpose

To demonstrate real-time embedded system design integrating sensing, control, communication, and safety mechanisms within a single microcontroller-based architecture.
