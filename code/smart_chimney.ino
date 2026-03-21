#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// === PIN DEFINITIONS ===
#define DHTPIN 2
#define DHTTYPE DHT22
#define MQ2_PIN A0
#define FAN_EN 9
#define FAN_IN1 4
#define FAN_IN2 5
#define BUZZER_PIN 10
#define BUTTON_PIN 3
#define GSM_RX 7
#define GSM_TX 8

#define DELAY_TIME_MS 3000 // delay before confirming gas leak

LiquidCrystal_I2C lcd(0x20, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial gsm(GSM_RX, GSM_TX);

// === VARIABLES ===
int fanSpeed = 0;
bool manualMode = false;
int buttonPressCount = 0;
unsigned long lastButtonPress = 0;

unsigned long gasStartTime = 0;
bool gasAlarmActive = false;
bool gsmNotified = false;

unsigned long tempHumStartTime = 0;
unsigned long tempHumEndTime = 0;

// === FUNCTION PROTOTYPES ===
void controlFan(int speed);
void displayFanStatus(float temp, float humidity);
void lcdPrint(String msg);
void checkGasAlarm();
void handleManualMode();
void handleAutoMode();
int calculateRequiredSpeed(float temp, float humidity);
void initGSM();
void sendSMSAndCall();

void setup() {
  pinMode(FAN_EN, OUTPUT);
  pinMode(FAN_IN1, OUTPUT);
  pinMode(FAN_IN2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  gsm.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  Serial.println("\n=== SMART CHIMNEY SYSTEM STARTING ===");
  lcd.setCursor(0, 0);
  lcd.print("Chimney System");
  delay(2000);
  lcd.clear();

  initGSM();
}

void loop() {
  // === Button Press Logic ===
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - lastButtonPress > 300) { // debounce
      buttonPressCount++;
      if (buttonPressCount > 4) {
        buttonPressCount = 0;
        manualMode = false;
        Serial.println("Switched to AUTO MODE");
      } else {
        manualMode = true;
        Serial.print("Manual Mode: Fan Level ");
        Serial.println(buttonPressCount);
      }
      lastButtonPress = millis();
    }
  }

  checkGasAlarm();

  if (!gasAlarmActive) {
    gsmNotified = false; // reset flag for next detection
    if (manualMode) handleManualMode();
    else handleAutoMode();
  }

  delay(500);
}

// === GSM INITIALIZATION ===
void initGSM() {
  Serial.println("Initializing SIM800L...");
  gsm.println("AT");
  delay(1000);
  gsm.println("AT+CMGF=1"); // text mode
  delay(1000);
  gsm.println("AT+CSCS=\"GSM\"");
  delay(1000);
  Serial.println("GSM Module Ready.");
}

// === GAS DETECTION ===
void checkGasAlarm() {
  int gasValue = analogRead(MQ2_PIN);

  if (gasValue > 300) {
    if (gasStartTime == 0) gasStartTime = millis();
    if (millis() - gasStartTime >= DELAY_TIME_MS) {
      if (!gasAlarmActive) {
        Serial.print("🔥 GAS/SMOKE detected! Value: ");
        Serial.println(gasValue);
      }
      gasAlarmActive = true;
    }
  } else {
    if (gasAlarmActive) {
      Serial.println("✅ Gas level normal again. System resuming normal operation.");
    }
    gasStartTime = 0;
    gasAlarmActive = false;
  }

  if (gasAlarmActive) {
    controlFan(3);
    tone(BUZZER_PIN, 1000);
    lcdPrint("Smoke Detected!");
    delay(200);
    noTone(BUZZER_PIN);
    delay(200);

    if (!gsmNotified) {
      sendSMSAndCall();
      gsmNotified = true;
    }
  } else {
    noTone(BUZZER_PIN);
  }
}

// === SEND SMS & MAKE CALL ===
void sendSMSAndCall() {
  String phoneNumber = "+919741912829";  // 🔹 Replace with your number
  String message = "ALERT! Smoke/Gas detected in chimney system. Fan running at highest speed.";

  Serial.print("📨 Sending SMS to ");
  Serial.println(phoneNumber);
  Serial.print("Message content: ");
  Serial.println(message);

  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");
  delay(1000);
  gsm.print(message);
  delay(1000);
  gsm.write(26); // CTRL+Z
  delay(3000);
  Serial.println("✅ SMS sent successfully!");

  // Make call
  Serial.print("📞 Dialing emergency call to ");
  Serial.println(phoneNumber);
  gsm.print("ATD");
  gsm.print(phoneNumber);
  gsm.println(";");
  delay(10000); // keep call for 10s
  gsm.println("ATH"); // hang up
  Serial.println("📴 Call ended.");
}

// === AUTO MODE ===
void handleAutoMode() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    lcdPrint("Sensor Error!");
    Serial.println("⚠️ DHT sensor error!");
    return;
  }

  int requiredSpeed = calculateRequiredSpeed(temp, humidity);

  if (requiredSpeed > 0) {
    tempHumEndTime = 0;
    if (tempHumStartTime == 0) tempHumStartTime = millis();
    if (millis() - tempHumStartTime >= DELAY_TIME_MS)
      fanSpeed = requiredSpeed;
  } else {
    tempHumStartTime = 0;
    if (fanSpeed > 0) {
      if (tempHumEndTime == 0) tempHumEndTime = millis();
      if (millis() - tempHumEndTime >= DELAY_TIME_MS)
        fanSpeed = 0;
    } else tempHumEndTime = 0;
  }

  controlFan(fanSpeed);
  displayFanStatus(temp, humidity);
}

// === MANUAL MODE ===
void handleManualMode() {
  int prevSpeed = fanSpeed;
  switch (buttonPressCount) {
    case 1: fanSpeed = 1; break;
    case 2: fanSpeed = 2; break;
    case 3: fanSpeed = 3; break;
    case 4: fanSpeed = 0; break;
    case 0: fanSpeed = 0; break;
  }

  if (fanSpeed != prevSpeed) {
    Serial.print("Manual Fan Speed set to ");
    Serial.println(fanSpeed);
  }

  controlFan(fanSpeed);
  displayFanStatus(0, 0);
}

// === FAN CONTROL ===
void controlFan(int speed) {
  digitalWrite(FAN_IN1, HIGH);
  digitalWrite(FAN_IN2, LOW);

  int pwm = 0;
  if (speed == 1) pwm = 130;
  else if (speed == 2) pwm = 190;
  else if (speed == 3) pwm = 255;
  analogWrite(FAN_EN, pwm);
}

// === LCD DISPLAY ===
void displayFanStatus(float temp, float humidity) {
  lcd.setCursor(0, 0);
  if (manualMode) lcd.print("MANUAL MODE     ");
  else {
    lcd.print("T:"); lcd.print(temp, 1); lcd.print((char)223); lcd.print("C ");
    lcd.print("H:"); lcd.print(humidity, 1); lcd.print("%  ");
  }

  lcd.setCursor(0, 1);
  if (fanSpeed == 0) lcd.print("Chimney OFF     ");
  else if (fanSpeed == 1) lcd.print("Fan Speed 1 (L) ");
  else if (fanSpeed == 2) lcd.print("Fan Speed 2 (M) ");
  else if (fanSpeed == 3) lcd.print("Fan Speed 3 (H) ");
}

void lcdPrint(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
}

// === CALCULATE FAN SPEED ===
int calculateRequiredSpeed(float temp, float humidity) {
  int tempSpeed = (temp > 40) ? 3 : (temp > 35) ? 2 : (temp > 30) ? 1 : 0;
  int humSpeed = (humidity > 90) ? 3 : (humidity > 82) ? 2 : (humidity > 77) ? 1 : 0;
  return max(tempSpeed, humSpeed);
}
