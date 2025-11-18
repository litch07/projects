# 📝 OptiWatt Project — LaTeX Source

This folder contains the full LaTeX source for the OptiWatt project paper, exported directly from Overleaf. All images and the `main.tex` file reside in the same directory (default Overleaf export structure).

---

## 📂 Project Structure

```
latex/
├── main.tex
├── 7DaysReading.png
├── appflow.png
├── autocut.png
├── booth1.jpg
├── booth2.jpg
├── esp32.png
├── occupancy.png
├── pzem-004t.jpg
├── pzemflow.png
├── relay.jpg
├── turnoffafterdelay.png
├── ultrasonic.jpg
└── website.png
```

All images are located in the same folder as `main.tex`, so no additional path configuration is required.

---

## ▶️ How to Compile

### **Option 1 — Overleaf**
1. Create a new project  
2. Drop all files from this folder  
3. Press **Recompile**

### **Option 2 — Local Compilation**
Requirements:
- TeX Live / MiKTeX / MacTeX  
- PDFLaTeX (recommended engine)

Compile using:

```bash
pdflatex main.tex
pdflatex main.tex
```

This produces:

```
main.pdf
```

---

## 📌 Notes
- Do **not** rename or move image files unless you update the paths in `main.tex`.
- Overleaf-style single-folder layout is fully supported and intentional.
- The PDF output should match the version included in `/docs/`.

---

## 👤 Maintainer
**Sadid Ahmed (litch07)**  
Primary author — Overleaf source owner
