# OptiWatt – Project Proposal

This folder contains the **project proposal** for **OptiWatt – Smart Energy Management System**, submitted as part of **EEE 2124: Electronics Laboratory** at **United International University (UIU)**, Trimester **Summer 252**, Group **07 (Section O)**.

The proposal describes the motivation, planned architecture, components, and expected features of OptiWatt before implementation.

---

## 📄 Files

- `OptiWatt_Project_Proposal.pdf` – final, exported version of the proposal  
- `OptiWatt_Project_Proposal.docx` – editable Word version of the proposal  

You can view the PDF directly in the browser, or open the Word file to revise or reuse the document.

---

## 🔍 Proposal Summary

OptiWatt proposes a **room-level smart energy management system** that combines:

- **Non-intrusive energy metering** using ESP32 + PZEM-004T AC energy monitors  
- **Occupancy-aware automation** using ultrasonic (and optionally PIR) sensing  
- **Automatic disconnection of non-critical loads** when the room is vacant  
- **Manual override and app/dashboard control** so users always remain in charge  
- **Billing transparency** through real-time monitoring, basic history, and cost estimation  

The target prototype focuses on accurate sensing, reliable occupancy detection, and safe control of a few representative loads.

---

## 🧱 System Components (Planned)

The proposal outlines the use of:

- **ESP32 Development Board** – main controller, Wi-Fi, sensor/relay interface  
- **PZEM-004T V3.0** – AC voltage, current, power, and kWh measurement  
- **Ultrasonic sensors (HC-SR04)** – doorway entry/exit and occupancy counting  
- **Relay modules** – switching non-critical AC loads (lights, plug, etc.)  
- Supporting components: fuses, terminals, wiring, and enclosures for safety

---

## ✨ Planned Features

1. **Real-Time Energy Monitoring** – continuous measurement of key electrical parameters  
2. **Vacancy-Based Power Cut** – turn off selected loads after the room becomes empty  
3. **User/App Control** – dashboard or app for manual toggling and settings  
4. **Usage & Bill Estimation** – approximate monthly bill and comparison to goals  

Flowcharts and diagrams in the document describe the core logic for occupancy, control, and monitoring.

---

## 👥 Authors

Group 07, Section O – EEE 2124 (Electronics Laboratory), UIU  

- Diba Jabin Fariha Tithy  
- Hujaifa Islam Johan  
- Md. Toufiq Imroz Khealid Khan  
- M. M. Sayem Prodhan  
- **Sadid Ahmed**
