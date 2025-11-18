# ⚡ OptiWatt – Smart Energy Management System

OptiWatt is a single-room smart energy management platform that combines real-time power monitoring with occupancy-based automation.  
The system uses an ESP32 microcontroller for data acquisition and control, AC power meters for load monitoring, ultrasonic sensors for entry/exit detection, and a lightweight web interface for visualization.

---

## 📌 Overview

OptiWatt provides:

- Real-time measurements of **voltage, current, power, energy (kWh), frequency, and power factor**  
- Occupancy detection using a dual-ultrasonic entry/exit sensor setup  
- Automatic load switching based on room occupancy  
- Monthly energy cost estimation using a slab-based tariff model  
- A built-in ESP32 web dashboard and a separate static Web UI prototype

---

## 📁 Repository Structure

The repository is organized into firmware, UI, documentation, and hardware resources.

| Folder | Description |
|-------|-------------|
| **[`firmware/`](firmware/)** | ESP32 source code (Arduino/PlatformIO). |
| **[`web-ui/`](web-ui/)** | Static prototype of the Web UI (HTML/CSS/JS). |
| **[`docs/`](docs/)** | Final report and LaTeX project files. |
| **[`hardware/`](hardware/)** | Circuit diagrams, wiring, and design assets. |

### Documentation and Schematics Layout

- **Final Report:** placed directly under `docs/` (e.g., `OptiWatt_Report.pdf`)  
- **LaTeX Source:** stored inside `docs/latex/`  
- **Hardware/Schematics:** stored inside `hardware/schematics/`

Example structure:

```
optiwatt/
├── firmware/
├── web-ui/
│   ├── index.html
│   ├── login.html
│   ├── rooms.html
│   ├── rooms.js
│   ├── devices.html
│   ├── styles.css
│   ├── pricing.js
│   └── script.js
├── docs/
│   ├── OptiWatt_Report.pdf
│   └── latex/
│       ├── main.tex
│       ├── 7DaysReading.png
│       ├── appflow.png
│       ├── autocut.png
│       ├── booth1.jpg
│       ├── booth2.jpg
│       ├── esp32.png
│       ├── fullcircuit.png
│       ├── goal.png
│       ├── occupancy.png
│       ├── pzem-004t.jpg
│       ├── pzemflow.png
│       ├── relay.jpg
│       ├── turnoffafterdelay.png
│       ├── ultrasonic.jpg
│       └── website.png
└── hardware/
    └── schematics/
        └── optiwatt_schematic.png
```

---

## 🔧 Firmware (ESP32)

The firmware located in `firmware/` handles:

- Interfacing with AC power meter modules (e.g., PZEM-004T)  
- Entry/exit detection using ultrasonic sensors  
- Occupancy counting and automation logic  
- Relay control for automatic load switching  
- Hosting a local web dashboard via HTTP  

### Running the Firmware

1. Open the firmware in **Arduino IDE** or **PlatformIO**  
2. Install ESP32 board support and required libraries  
3. Configure:
   - Wi-Fi credentials  
   - Sensor pins  
   - Relay pins  
4. Build and upload to the ESP32  
5. Open the Serial Monitor to view the assigned IP address  
6. Access the dashboard in a browser:

```
http://<ESP32_IP_ADDRESS>/
```

---

## 🌐 Web UI Prototype

The `web-ui/` folder contains a static UI prototype. It is not connected to the firmware yet.

### To preview:

```bash
git clone https://github.com/litch07/projects.git
cd projects/electronics-lab/optiwatt/web-ui
```

Then open `index.html` in any browser.

No server is required.

---

## 📄 Documentation

- Final report: `docs/OptiWatt_Report.pdf`  
- Full LaTeX project: `docs/latex/`

---

## 🧩 Hardware Resources

Schematics and hardware references are located in:

```
hardware/schematics/
```

---

## 🔭 Future Improvements

- Connect the Web UI to live device data  
- Add historical data logging and charts  
- Improve automation rules (multi-room, thresholds, timers)  
- Enhance mobile responsiveness and UI layout  

---

## 👤 Maintainer

**Sadid Ahmed (litch07)**  
Firmware, documentation, hardware integration, and UI structure.
