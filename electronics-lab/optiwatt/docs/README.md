# 📄 OptiWatt Documentation

This directory contains all documentation related to the **OptiWatt Smart Energy Management System**, including the final project report and the full LaTeX source used to generate it.

---

## 📘 Final Report (PDF)

The final submitted version of the documentation is available here:

👉 **OptiWatt_Report.pdf**

This PDF contains the complete description of the system, including:
- Project overview and objectives  
- Hardware architecture  
- ESP32 firmware structure  
- Web interface design  
- Energy monitoring methodology  
- Occupancy tracking logic  
- Results, testing, and analysis  

---

## 📝 LaTeX Source Files

All LaTeX files used to compile the report are stored in:

```
docs/latex/
```

This folder includes:
- `main.tex` – primary document file  
- Section `.tex` files (occupancy, firmware, sensors, circuit, etc.)  
- Images, diagrams, and flowcharts  
- Tables, references, and bibliography  

You may import this folder into **Overleaf** or any LaTeX environment to rebuild or modify the project report.

---

## 📁 Folder Structure

```
    docs/
    ├── proposal/
    │   ├── OptiWatt_Project_Proposal.docx
    │   └── OptiWatt_Project_Proposal.pdf
    ├── OptiWatt_Report.pdf
    └── latex/
       ├── main.tex
       ├── 7DaysReading.png
       ├── appflow.png
       ├── autocut.png
       ├── booth1.jpg
       ├── booth2.jpg
       ├── esp32.png
       ├── fullcircuit.png
       ├── goal.png
       ├── occupancy.png
       ├── pzem-004t.jpg
       ├── pzemflow.png
       ├── relay.jpg
       ├── turnoffafterdelay.png
       ├── ultrasonic.jpg
       └── website.png
```

---

## ⚠️ Notes for Contributors

- Do **not** edit the PDF directly; modify the LaTeX source in `/latex`.
- Keep all figures inside `/latex/images`.
- When adding new sections, update `main.tex` accordingly.
- If the LaTeX build breaks, check for missing image references or packages.

---

## 👤 Author
**Sadid Ahmed (litch07)**  
Documentation writer & project developer

