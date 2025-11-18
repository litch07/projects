# OptiWatt – Project Proposal

This folder contains the **project proposal** for **OptiWatt – Smart Energy Management System**, submitted as part of the course **EEE 2124: Electronics Laboratory** at **United International University (UIU)**, Trimester **Summer 252**, Group **07 (Section O)**.

The proposal outlines the motivation, system design, components, and planned features of OptiWatt before implementation.

---

## 📄 Document

- `OptiWatt_Project_Proposal.pdf`  
  Formal proposal describing the planned single-room smart energy management system.

---

## 🔍 Proposal Summary

OptiWatt proposes a **room-level smart energy management system** that combines:

- **Non-intrusive energy metering** using ESP32 + PZEM-004T AC energy monitors  
- **Occupancy-aware automation** using dual ultrasonic sensors and a PIR sensor  
- **Automatic disconnection of non-critical loads** when the room is vacant  
- **Manual override and app control** so users always stay in charge  
- **Billing transparency** through real-time monitoring, historical usage, and projected costs  

Target performance (prototype stage):

- Power measurement accuracy around **±2%**  
- Occupancy detection reliability of **≈98%**

---

## 🧱 System Components (Planned)

The proposal describes the following key components:

- **ESP32 Development Board** – main controller, Wi-Fi, sensor & relay interface  
- **PZEM-004T V3.0** – AC voltage, current, power, and kWh measurement  
- **Dual HC-SR04 Ultrasonic Sensors** – doorway entry/exit and occupancy counting  
- **HC-SR501 PIR Sensor** – motion confirmation to avoid false vacancy detection  
- **Relay Modules** – safe switching of non-critical AC loads (lights, fans, etc.)  
- **Enclosure, fuses, terminals, wiring** – electrical safety and physical separation of low/high voltage

---

## ✨ Planned Features (from Proposal)

The proposal focuses on four main feature areas:

1. **Real-Time Energy Monitoring**  
   Continuous measurement of voltage, current, power, and cumulative energy, with filtering and logging.

2. **Vacancy-Based Automatic Power Cut**  
   Use occupancy information to disconnect non-critical loads after a safe delay when the room is empty.

3. **App Control & Manual Override**  
   Mobile app/dashboard for manual toggling, settings, and overriding automation when needed.

4. **Monthly Usage Estimation & Goal Tracking**  
   Daily kWh aggregation, monthly bill estimation, and comparison against user-defined energy goals.

The document also includes **flowcharts** for occupancy counting, power cut logic, energy monitoring, goal tracking, and manual override.

---

## 🛡️ Safety, Cost & Future Scope

The proposal addresses:

- **Safety:** fusing, isolation, clearances, and fail-safe defaults for critical loads  
- **Approximate Cost:** itemized bill of materials for the prototype  
- **Testing Plan:** accuracy tests, occupancy scenario tests, automation/override checks, and end-to-end trials  
- **Future Scope:** multi-room expansion, advanced analytics, smart-assistant/cloud integration, and refined hardware (PCBs, professional enclosures)

---

## 👥 Authors

Group 07, Section O – EEE 2124 (Electronics Laboratory), UIU  

- Diba Jabin Fariha Tithy  
- Hujaifa Islam Johan  
- Md. Toufiq Imroz Khealid Khan  
- M. M. Sayem Prodhan  
- **Sadid Ahmed**

