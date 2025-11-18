# 🔧 OptiWatt Hardware Resources

This directory contains **all hardware-related files** for the OptiWatt system, including wiring diagrams, block diagrams, schematics, and circuit design documentation.

The hardware layer covers sensors, relays, ESP32 interfacing, and AC power monitoring integration.

---

## 📂 Contents

```
hardware/
├── schematics/
│   ├── optiwatt_schematic.png
│   └── README.md
└── README.md
```

---

## 🏗️ Hardware Components

The OptiWatt system includes:

- **ESP32 DevKit V1** (main controller)  
- **PZEM-004T v3.0** AC energy meters  
- **Dual Ultrasonic Sensors** for occupancy  
- **Relays (5V)** for LED and Plug control  
- **DC power supply + level shifting (if required)**  
- **Manual switches** for local override  

---

## 📘 What You’ll Find Here

- Complete system schematic  
- Wiring diagram for ESP32 + relays + sensors  
- PZEM-004T connection references  
- Block diagram for entire device flow  
- Hardware layout used in the implementation  

These diagrams support the firmware implementation found in `firmware/`.

---

## 🛠 Usage Notes

- Always verify AC wiring separately — **mains voltage is dangerous**.  
- PZEM modules use TTL serial; ensure correct RX/TX mapping.  
- Ultrasonic sensors require stable 5V supply.  
- Relay modules must use proper isolation if connected to AC loads.

---

## 👤 Maintainer
**Sadid Ahmed (litch07)**  
Hardware design & system integration
