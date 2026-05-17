# ☀️ Smart Solar Monitoring & Management System
### *An Autonomous IoT Solution for Rural Energy Optimization*

This project addresses the critical efficiency gaps in stationary solar installations by integrating **Dual-Axis Tracking**, **Automated Dust Mitigation**, and **Active Thermal Regulation**. By leveraging the **ESP32** microcontroller and **MQTT protocol**, the system provides a closed-loop environment where real-time sensor data from the field is transformed into actionable energy analytics on a custom-built web dashboard.

---
### 🎯 Core Objectives

1. **Efficiency Maximization:** Increase photovoltaic yield by 30-40% via real-time sun-path alignment.
2. **Predictive Maintenance:** Monitor dust accumulation and voltage drops to trigger autonomous cleaning.
3. **Hardware Longevity:** Prevent cell degradation through automated cooling when temperatures exceed 35°C.
4. **Remote Accessibility:** Enable global system management through a cloud-synced web interface.

---

## 🚀 Key Features

* **Dual-Axis Tracking:** Maximizes energy harvest by following the sun's path using 4 LDR sensors and high-torque servos.
* **Automated Maintenance:**
    * **Cooling:** Temperature-triggered water pump system (DHT22 sensor).
    * **Cleaning:** Remote-controlled wiper mechanism to remove dust.
* **IoT Dashboard:** Real-time data visualization via **Adafruit IO** and a custom **Tailwind CSS** web interface.
* **Performance Analytics:** Live tracking of Voltage, Current, Power, and Battery State of Charge (SoC).

---
## 📸 Project Showcase

### 🖥️ Live Dashboard

*A custom-built web interface using Tailwind CSS and Chart.js. This dashboard fetches live telemetry from the ESP32 via Adafruit IO, displaying real-time power generation, efficiency metrics, and system health alerts.*

![Live Dashboard](Media/Web%20page.png)


---

### 🛠️ Full Hardware Prototype

*The complete integrated system featuring the solar panel, dual-axis tracking servos, and the relay-controlled cleaning and cooling hardware. It demonstrates the full physical execution of the microgrid monitor.*

![Hardware Build](Media/Hardware%20model%20using%20esp32.jpeg)


---

### ☀️ Specialized Tracking Model

*A standalone dual-axis tracker prototype used for calibrating the LDR differential logic. This unit focuses exclusively on sun-path optimization before integration into the larger system.*

![Solar Tracker](Media/Seperate%20Solar%20tracking%20model.jpeg)


---

### 🎥 System Demos

*Demonstrates the automated cooling pump activating via temperature thresholds and the remote-triggered wiper system for dust removal.*

* **[▶️ Cleaning & Cooling Process Demo](Media/Cleaning%20and%20cooling%20process%20model.mp4)**

* *Showcases the dual-axis movement of the high-torque servos as they orient the solar panel toward the strongest light source in real-time.*

* **[▶️ Solar Motor Functioning Demo](Media/Motor%20functioning%20on%20solar%20panel.mp4)**
  

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

---

## 🗺️ Future Roadmap
* **Deep Sleep Integration:** Optimize ESP32 power consumption for night-time operation.
* **LoRaWAN Support:** Enable long-range communication for truly remote rural areas where WiFi is unavailable.
* **Predictive Analytics:** Use historical data to predict peak generation hours and maintenance schedules.
* **Mobile App:** Develop a native Android/iOS application for push-notification alerts.

---

## 🤝 Contributing
Contributions, issues, and feature requests are welcome! Feel free to check the [issues page](link-to-your-issues-tab) if you want to contribute to the code or suggest improvements.
