# ☀️ Smart Solar Monitoring & Management System

An autonomous IoT-based solution for solar energy optimization, featuring dual-axis tracking, automated cleaning, and thermal management.

---

## 🚀 Key Features
* **Dual-Axis Tracking:** Maximizes energy harvest by following the sun's path using 4 LDR sensors and high-torque servos.
* **Automated Maintenance:** * **Cooling:** Temperature-triggered water pump system (DHT22 sensor).
    * **Cleaning:** Remote-controlled wiper mechanism to remove dust.
* **IoT Dashboard:** Real-time data visualization via **Adafruit IO** and a custom **Tailwind CSS** web interface.
* **Performance Analytics:** Live tracking of Voltage, Current, Power, and Battery State of Charge (SoC).

---

## 📸 Project Showcase

### 🖥️ Live Dashboard
![Live Dashboard](Media/Web%20page%20preview.png)
*Real-time analytics showing efficiency curves and environmental data.*

### 🛠️ Hardware Prototype
![Hardware Build](Media/Hardware%20model%20using%20esp%2032.jpeg)
*Dual-axis tracking structure with integrated cleaning and cooling modules.*

### 🎥 System Demo
[▶️ Click here to watch the Cleaning & Cooling Process](Media/Cleaning%20and%20cooling%20process%20model.mp4)

[▶️ Click here to watch the Solar Motor Functioning](Media/Motor%20functioning%20on%20solar%20panel.mp4)

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
1. **Hardware:** Wire the components as per the circuit diagram.
2. **Adafruit IO:** Create feeds: `voltage`, `current`, `temp`, `humidity`, `battery`, `manual-cleaning`, and `manual-cooling`.
3. **Firmware:** Upload `Firmware/Solar_System_Firmware.ino` to your ESP32.
4. **Web App:** Update `Web-Dashboard/script.js` with your credentials and open `index.html`.

---

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
