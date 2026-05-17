<img width="1920" height="1170" alt="Web page preview" src="https://github.com/user-attachments/assets/180d3e58-b555-4b8b-8d25-a1ce56cf0bd1" /># ☀️ Smart Solar Monitoring & Management System

An autonomous IoT-based solution for solar energy optimization, featuring dual-axis tracking, automated cleaning, and thermal management.

---

## 🚀 Key Features
* **Dual-Axis Tracking:** Maximizes energy harvest by following the sun's path using 4 LDR sensors and high-torque servos.
* **Automated Maintenance:** * **Cooling:** Temperature-triggered water pump system (DHT22 sensor).
    * **Cleaning:** Remote-controlled wiper mechanism to remove dust.
* **IoT Dashboard:** Real-time data visualization via **Adafruit IO** and a custom **Tailwind CSS** web interface.
* **Performance Analytics:** Live tracking of Voltage, Current, Power, and Battery State of Charge (SoC).

---

## 📊 System Architecture
The system uses an ESP32 as the central controller, communicating via MQTT to the cloud.



---

## 📸 Project Showcase

### 🖥️ Live Dashboard
![Web Dashboard](Web page preview.png)
*Real-time analytics showing efficiency curves and environmental data.*

### 🛠️ Hardware Prototype
![Hardware Build](Hardware model using esp 32.jpg)
*Dual-axis tracking structure with integrated cleaning and cooling modules.*

### 🎥 System Demo
[Click here to watch the solar motor Demo](Cleaning and cooling process model.mp4)(Motor functioning on solar panel.mp4)
*The demo shows the panel tracking a light source and the cleaning mechanism being triggered from the web app.*

---

## 🔧 Hardware Components
| Component | Function |
| :--- | :--- |
| **ESP32** | Main Microcontroller (WiFi enabled) |
| **INA219** | DC Voltage & Current Sensor |
| **DHT22** | Temp & Humidity Sensor |
| **MG996R Servos** | Horizontal & Vertical Actuators |
| **Relay Module** | Wiper & Pump Control |
| **LDRs (x4)** | Solar Position Sensing |

---

## 🛠️ Installation & Setup
1.  **Hardware:** Wire the components as per the circuit diagram (found in the Hardware folder).
2.  **Adafruit IO:** Create feeds named: `voltage`, `current`, `temp`, `humidity`, `battery`, `manual-cleaning`, and `manual-cooling`.
3.  **Firmware:** Upload `Firmware/Solar_System.ino` to your ESP32 after updating your WiFi and Adafruit credentials.
4.  **Web App:** Update `Web-Dashboard/script.js` with your Adafruit Username and Key, then open `index.html` in your browser.

---

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Finalized professional README with media and documentation.
