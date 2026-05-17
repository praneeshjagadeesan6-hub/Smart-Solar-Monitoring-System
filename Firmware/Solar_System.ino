#include <WiFi.h>
#include <Adafruit_INA219.h>
#include <ESP32Servo.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"

// ==========================
// CONFIGURATION
// ==========================
#define WLAN_SSID       "YOUR_WIFI_SSID"
#define WLAN_PASS       "YOUR_WIFI_PASSWORD"
#define AIO_USERNAME    "YOUR_ADAFRUIT_USERNAME"
#define AIO_KEY         "YOUR_ADAFRUIT_IO_KEY"

// Pins
#define DHTPIN          4       
#define DHTTYPE         DHT22
#define RELAY_PUMP      14      
#define RELAY_WIPER     27      
#define SERVO_H_PIN     13      
#define SERVO_V_PIN     12      
#define LDR_TL          32      
#define LDR_TR          33
#define LDR_BL          34
#define LDR_BR          35

// Thresholds
const float TEMP_THRESHOLD = 35.0; // Auto-cool above this
const int LDR_TOLERANCE = 100;    // Jitter protection for servos

// ==========================
// OBJECTS & GLOBALS
// ==========================
DHT dht(DHTPIN, DHTTYPE);
Adafruit_INA219 ina219;
Servo servoH, servoV;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, AIO_USERNAME, AIO_KEY);

// Publishing Feeds
Adafruit_MQTT_Publish p_volt = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/voltage");
Adafruit_MQTT_Publish p_curr = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/current");
Adafruit_MQTT_Publish p_temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish p_humi = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish p_batt = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/battery");

// Subscribing Feeds (Manual Overrides from Web)
Adafruit_MQTT_Subscribe s_clean = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/manual-cleaning");
Adafruit_MQTT_Subscribe s_cool  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/manual-cooling");

unsigned long lastUpdate = 0;
int posH = 90;
int posV = 90;

void setup() {
  Serial.begin(115200);
  
  // Start Sensors
  dht.begin();
  if (!ina219.begin()) Serial.println("INA219 Error!");

  // Setup Actuators
  servoH.attach(SERVO_H_PIN);
  servoV.attach(SERVO_V_PIN);
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_WIPER, OUTPUT);
  digitalWrite(RELAY_PUMP, LOW);
  digitalWrite(RELAY_WIPER, LOW);

  // Connect WiFi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  
  // Setup Subscriptions
  mqtt.subscribe(&s_clean);
  mqtt.subscribe(&s_cool);
  Serial.println("\nSystem Ready!");
}

void loop() {
  MQTT_connect();

  // 1. DUAL-AXIS SOLAR TRACKING
  int tl = analogRead(LDR_TL);
  int tr = analogRead(LDR_TR);
  int bl = analogRead(LDR_BL);
  int br = analogRead(LDR_BR);

  int avgTop = (tl + tr) / 2;
  int avgBot = (bl + br) / 2;
  int avgLeft = (tl + bl) / 2;
  int avgRight = (tr + br) / 2;

  // Vertical Adjustment
  if (abs(avgTop - avgBot) > LDR_TOLERANCE) {
    if (avgTop < avgBot && posV < 170) posV++;
    if (avgTop > avgBot && posV > 10) posV--;
  }
  // Horizontal Adjustment
  if (abs(avgLeft - avgRight) > LDR_TOLERANCE) {
    if (avgLeft < avgRight && posH < 170) posH++;
    if (avgLeft > avgRight && posH > 10) posH--;
  }
  servoV.write(posV);
  servoH.write(posH);

  // 2. DATA SENSING
  float voltage = ina219.getBusVoltage_V();
  float current = ina219.getCurrent_mA();
  float temp    = dht.readTemperature();
  float humi    = dht.readHumidity();
  // Battery SoC Estimation for 12V Lead Acid
  int battery = map(constrain(voltage * 10, 105, 127), 105, 127, 0, 100);

  // 3. AUTO-COOLING LOGIC (Hardcoded for Safety)
  if (temp > TEMP_THRESHOLD) {
    digitalWrite(RELAY_PUMP, HIGH); 
  } else if (temp < (TEMP_THRESHOLD - 5)) {
    digitalWrite(RELAY_PUMP, LOW);
  }

  // 4. PUBLISH TO ADAFRUIT (Every 10 Seconds)
  if (millis() - lastUpdate > 10000) {
    if (!p_volt.publish(voltage)) Serial.println("Volt Publish Failed");
    p_curr.publish(current);
    p_temp.publish(temp);
    p_humi.publish(humi);
    p_batt.publish(battery);
    lastUpdate = millis();
  }

  // 5. RECEIVE WEB COMMANDS (Manual Override)
  Adafruit_MQTT_Subscription *subscription;
  while ((subscription = mqtt.readSubscription(5))) {
    if (subscription == &s_clean) {
       // Expects "1" for ON, "0" for OFF from your Web Button
       int state = atoi((char *)s_clean.lastread);
       digitalWrite(RELAY_WIPER, state == 1 ? HIGH : LOW);
       Serial.print("Manual Clean: "); Serial.println(state);
    }
    if (subscription == &s_cool) {
       int state = atoi((char *)s_cool.lastread);
       digitalWrite(RELAY_PUMP, state == 1 ? HIGH : LOW);
       Serial.print("Manual Cool: "); Serial.println(state);
    }
  }

  delay(50); // Small stability delay
}

// Ensure MQTT stays connected
void MQTT_connect() {
  if (mqtt.connected()) return;
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while (mqtt.connect() != 0) {
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) return;
  }
  Serial.println("MQTT Connected!");
}
