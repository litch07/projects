# 💡 OptiWatt – Smart Energy Management System

OptiWatt is a **single-room smart energy management system** that combines real-time power monitoring with **occupancy-aware automation**.

It uses an **ESP32** as the main controller, AC power meters for per-load monitoring, ultrasonic sensors for occupancy detection, and a web interface for monitoring and control.

---

## ⚡ Overview

OptiWatt is designed to:

* Measure per-load **voltage, current, power, energy (kWh), power factor, frequency**.
* Detect room **occupancy** (entry/exit) using non-imaging ultrasonic sensors.
* Automatically switch selected loads **ON/OFF based on occupancy**.
* Estimate **energy cost** using a slab-based tariff model.
* Provide a **local dashboard** and a **separate Web UI prototype** for richer visualization.

---

## 📂 Repository Layout

This project is organized into separate folders for firmware, UI, documentation, and hardware.

| Folder | Key Contents |
| :--- | :--- |
| **[`firmware/`](firmware/)** | Arduino/PlatformIO source files. |
| **[`web-ui/`](web-ui/)** | Static Web UI prototype. |
| **[`docs/`](docs/)** | Final Paper PDF, LaTeX source files. |
| **[`hardware/`](hardware/)** | Schematics, wiring, and block diagrams. |

### Documentation and Schematics Structure

* **Final Paper PDF:** Should be placed directly in [`docs/`](docs/) (e.g., `docs/OptiWatt_Report.pdf`).
* **LaTeX Source:** Place all source files under [`docs/latex/`](docs/latex/).
* **Schematics:** Place all diagrams and design files under [`hardware/schematics/`](hardware/schematics/) (e.g., `hardware/schematics/optiwatt_schematic.png`).

A minimal structure might look like:

```text
optiwatt/
├── firmware/
│   └── ... ESP32 code ...
├── web-ui/
│   ├── index.html
│   ├── styles.css
│   └── script.js
└── docs/
│   ├── OptiWatt_Report.pdf
│   └── latex/
│       ├── main.tex
│       ├── 7DaysReading.tex
│       ├── appflow.tex
│       ├── autocut.tex
│       ├── booth1.tex
│       ├── booth2.tex
│       ├── esp32.tex
│       ├── fullcircuit.tex
│       ├── goal.tex
│       ├── occupancy.tex
│       ├── pzem-004t.tex
│       ├── pzemflow.tex
│       ├── relay.tex
│       ├── turnoffafterdelay.tex
│       ├── ultrasonic.tex
│       └── website.tex
├── hardware/
│   └── schematics/
│       └── optiwatt_schematic.png
└── README.md

```

## 🔧 Firmware (ESP32)

The firmware (in [`firmware/`](firmware/)) is responsible for:

* Reading measurements from AC power meter modules (e.g., PZEM-004T).
* Handling ultrasonic sensors for entry/exit detection and occupancy count.
* Running the automation logic (e.g., turn loads off when the room is vacant).
* Serving a built-in web page over HTTP on the local network.

### How to Run (Firmware)

1.  Open the code from [`firmware/`](firmware/) in **Arduino IDE** or **PlatformIO**.
2.  Install the required **ESP32 board support** and any libraries used (e.g., PZEM004T driver).
3.  **Update:**
    * Wi-Fi credentials.
    * GPIO pin mappings for sensors, relays, etc.
4.  Select the correct ESP32 board and port, then **compile and upload**.
5.  After boot, check the Serial Monitor for the assigned IP address.
6.  Open a browser on the same network and visit:
    ```
    http://<ESP32_IP_ADDRESS>/
    ```
    to access the built-in dashboard.

---

## 🌐 Web UI Prototype

The Web UI prototype in [`web-ui/`](web-ui/) is a static frontend for OptiWatt:

* Built with **HTML, CSS, and vanilla JavaScript**.
* Designed to show **room and device-level energy usage, daily/monthly cost,** device states, and automation toggles.
* Currently uses **demo/simulated data only** (no live hardware connection yet).

### Previewing the Web UI

```bash
cd web-ui
# Then open index.html in your browser
```

---

## 📄 Paper & LaTeX

The final report/paper:
[`docs/OptiWatt_Report.pdf`](docs/OptiWatt_Report.pdf)

The LaTeX source:
[`docs/latex/`](docs/latex/)

---

## 🧩 Hardware & Schematics

All hardware-related visuals and design files belong under [`hardware/`](hardware/), specifically:
[`hardware/schematics/`](hardware/schematics/)

---

## 🔮 Future Work

* Connect the Web UI to live firmware via **REST/WebSocket API**.
* Add **historical data logging** and trend charts.
* Extend automation (time-based, thresholds, multi-room).
* Polish UI/UX and improve mobile responsiveness.

---

## 👤 Maintainer

[**Sadid Ahmed (litch07)**](https://github.com/litch07) – firmware, documentation, and repository structure.
