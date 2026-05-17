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
![Live Dashboard](Media/Web%20page.png)
*A custom-built web interface using Tailwind CSS and Chart.js. This dashboard fetches live telemetry from the ESP32 via Adafruit IO, displaying real-time power generation, efficiency metrics, and system health alerts.*

---

### 🛠️ Full Hardware Prototype
![Hardware Build](Media/Hardware%20model%20using%20esp32.jpeg)
*The complete integrated system featuring the solar panel, dual-axis tracking servos, and the relay-controlled cleaning and cooling hardware. It demonstrates the full physical execution of the microgrid monitor.*

---

### ☀️ Specialized Tracking Model
![Solar Tracker](Media/Seperate%20Solar%20tracking%20model.jpeg)
*A standalone dual-axis tracker prototype used for calibrating the LDR differential logic. This unit focuses exclusively on sun-path optimization before integration into the larger system.*

---

### 🎥 System Demos

* **[▶️ Cleaning & Cooling Process Demo](Media/Cleaning%20and%20cooling%20process%20model.mp4)**
  *Demonstrates the automated cooling pump activating via temperature thresholds and the remote-triggered wiper system for dust removal.*

* **[▶️ Solar Motor Functioning Demo](Media/Motor%20functioning%20on%20solar%20panel.mp4)**
  *Showcases the dual-axis movement of the high-torque servos as they orient the solar panel toward the strongest light source in real-time.*

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
