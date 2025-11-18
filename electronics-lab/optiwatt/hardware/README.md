# 🔧 OptiWatt Hardware Resources

This directory contains **hardware-related files** for the OptiWatt system, currently including the wiring diagram.  
It covers ESP32 interfacing, relays, sensors, and AC power monitoring connections.

---

## 📂 Contents

```
hardware/
├── schematics/
│   ├── wiring_diagram.png
│   └── README.md
└── README.md
```

---

## 🏗️ Hardware Components

The OptiWatt system uses:

- **ESP32 DevKit V1** (main controller)  
- **PZEM-004T v3.0** AC energy meter  
- **Dual Ultrasonic Sensors** for occupancy detection  
- **Relays (5V)** for LED and plug control  
- **DC power supply** for sensors and relays  
- **Manual switches** for local override  

---

## 📘 Wiring Diagram

The diagram shows physical connections for:  

- ESP32 pins  
- PZEM-004T RX/TX and AC connections  
- Relays controlling LEDs and plugs  
- Ultrasonic sensor wiring  
- Power distribution  

It is ideal for breadboard prototyping, PCB planning, and final installation.

---

## 🛠 Usage Notes

- Verify wiring matches firmware pin definitions.  
- Ensure proper isolation when handling AC loads.  
- Provide stable power for sensors and relays.  

---

## 👤 Maintainer
**Sadid Ahmed (litch07)**  
Hardware design & system integration
