# ⚡ OptiWatt – ESP32 Smart Energy Management Firmware

This folder contains the **OptiWatt ESP32 firmware**, responsible for real-time power monitoring, occupancy-based automation, and the built-in web dashboard used for controlling booth devices.

The firmware runs entirely on an **ESP32 DevKit V1** and integrates sensors, relays, and PZEM energy meters into a unified smart-booth system.

---

## 🚀 Features

### 🔌 Device Control
- Individual control of **LED** and **Plug** loads  
- Physical switches + Web controls  
- Automation hierarchy:  
  **Manual Action → Device Automation → Global Automation**

### 👤 Occupancy Detection
- Dual ultrasonic sensors (Door + Inside)
- Entry/Exit pairing logic
- Median filtering + debounce + refractory delay
- Automatic OFF when booth becomes vacant

### ⚡ Energy Monitoring (PZEM-004T)
- Voltage, current, power, energy (kWh)
- Per-device modules using unique PZEM addresses:
  - LED → `0x02`
  - Plug → `0x03`

### 🌐 Embedded Web Dashboard
- Runs directly from the ESP32 (AP Mode)
- Control LEDs, plug, and automation states
- Shows real-time sensor readings and goals
- Clean mobile-friendly layout

### 💾 Persistent Storage
Stored via Preferences:
- Global automation state  
- LED & Plug automation  
- User energy goals  

---

## 📡 Default Wi-Fi AP

```
SSID: OptiWatt
Password: PasswordNai
```

Dashboard URL:
```
http://192.168.4.1/
```

---

## 🔧 Hardware Connections

### Relays & Switches
| Component | Pin |
|----------|-----|
| LED Relay | 14 |
| Plug Relay | 26 |
| LED Switch | 25 |
| Plug Switch | 33 |

### Ultrasonic Sensors
| Sensor | Trigger | Echo |
|--------|---------|------|
| Door | 5 | 18 |
| Inside | 4 | 19 |

### PZEM-004T (UART2)
| Line | Pin |
|------|-----|
| RX | 16 |
| TX | 17 |

---

## 🛠️ Flashing Instructions

1. Install ESP32 support in Arduino IDE  
2. Select board: **ESP32 Dev Module**  
3. Install required libraries (PZEM004T, Preferences, etc.)  
4. Connect ESP32 and upload the firmware  
5. Connect to Wi-Fi network **OptiWatt**  
6. Visit:  
   ```
   http://192.168.4.1/
   ```

---

## 📁 File Structure
```
firmware/
└── OptiWatt.ino
└── README.md
```

---

## 🔮 Future Improvements
- Live chart updates  
- REST/WebSocket API  
- Multi-room expansion  
- Advanced scheduling & thresholds  

---

## 👤 Author
**Sadid Ahmed (litch07)**  
Firmware & system architecture  
GitHub: https://github.com/litch07
