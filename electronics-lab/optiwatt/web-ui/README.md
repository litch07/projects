# OptiWatt Web UI Prototype

The **OptiWatt Web UI** is a lightweight, static frontend prototype for the OptiWatt Smart Energy Management System.  
It demonstrates the planned interface for monitoring room appliances, visualizing energy usage, and controlling devices.

This prototype is **frontend-only** and does not yet communicate with the ESP32 firmware.

---

## ✨ Features

- Multi-room and per-device views for navigating appliances  
- Dashboard showing daily and monthly consumption and cost  
- UI elements for device ON/OFF, auto-cut status, and occupancy indicators  
- Goal-tracking panels for daily and monthly energy limits  
- Responsive layout designed for both desktop and mobile  
- Modular JavaScript structure for easy integration with future APIs  

---

## 🛠 Built With

- **HTML5**
- **CSS3** (utility-based layout)
- **Vanilla JavaScript** (modular structure)
- **Chart.js** (usage visualization – demo data only)

No frameworks, build tools, or external dependencies are required.  
The interface runs as a simple static webpage.

---

## ▶️ Previewing the Web UI

If you have cloned the main repository:

```bash
git clone https://github.com/litch07/projects.git
cd projects/electronics-lab/optiwatt/web-ui
```


Then open `index.html` in a browser:

Windows
```Bash
start index.html
```
macOS
```Bash
open index.html
```

Linux
```Bash
xdg-open index.html
```
Note: All data is currently demo/simulated; there is no live connection to the ESP32 yet.

## 👤 Maintainer

**Sadid Ahmed (litch07)**  
Firmware, documentation, hardware integration, and UI structure.
