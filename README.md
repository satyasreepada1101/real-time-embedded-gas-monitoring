---

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

---

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
2. Select Board: **Arduino Uno**
3. Select correct COM Port
4. Click **Upload**

---

## 📱 GSM Configuration

Before uploading:

Edit this line inside the code:

```cpp
String phoneNumber = "+91XXXXXXXXXX";
```

Replace with your own phone number.

Insert a valid 2G-enabled SIM card into SIM800L.

Ensure proper external power supply for GSM module (it requires high current during transmission).

---

## ⚠️ Important Notes

- MQ-2 sensor requires initial warm-up (~30–60 seconds).
- SIM800L works only with 2G networks.
- Ensure stable power supply to avoid GSM reset issues.
- Threshold values can be adjusted in the `calculateRequiredSpeed()` function.

---

## 🧪 Testing Procedure

1. Power ON the system.
2. Wait for sensor stabilization.
3. Introduce smoke near MQ-2 sensor.
4. After confirmation delay:
   - Buzzer should activate
   - Fan should run at max speed
   - SMS should be received
   - Call should be initiated

---
