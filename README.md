# 🔥 Real-Time Embedded Gas Monitoring & Ventilation System

## 📌 Overview
This project implements a real-time embedded gas monitoring and automated ventilation system using Arduino and Embedded C.

The system continuously monitors temperature, humidity, and gas/smoke concentration in a kitchen environment. Based on sensor readings, it dynamically adjusts ventilation speed. In hazardous situations, it activates an alarm and sends remote alerts using a GSM module.

---

## 🏗 System Architecture
The system consists of:

- **Input Layer**
  - DHT22 – Temperature & Humidity sensing
  - MQ-2 – Gas/Smoke detection
  - Push Button – Manual override control

- **Processing Layer**
  - Arduino Uno (ATmega328P)
  - Threshold evaluation logic
  - Non-blocking timing using `millis()`
  - Multi-mode control (Auto / Manual / Emergency)

- **Output Layer**
  - 12V DC Fan (PWM controlled via L298N driver)
  - Passive Buzzer (audio alert)
  - 16x2 I2C LCD (real-time system display)
  - SIM800L GSM module (SMS + Call alert)

---

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

---

## 🧠 Core Logic Implementation

- Gas detection uses analog threshold monitoring with timed confirmation logic.
- Auto mode calculates required fan speed using dominant environmental parameter.
- Manual mode cycles through speed levels using button debouncing.
- Safety logic overrides all other operations when gas is detected.

---

## ⚙️ Technologies Used

- Embedded C
- Arduino IDE
- Sensor Integration
- PWM Motor Control
- AT Command Communication (GSM)
- I2C Communication
- Serial Debugging

---

## 📸 Project Images

### Circuit Setup
![Circuit](images/pic%201.png)

### Hardware Setup
![Hardware](images/pic%202.png)

### Working Model
![Working](images/working%20model.png)

---

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

---

## 🎯 Purpose

To demonstrate real-time embedded system design integrating sensing, control, communication, and safety mechanisms within a single microcontroller-based architecture.
