# UIU CGPA Calculator – Java Swing

A simple **CGPA & GPA calculator** built using **Java Swing**, designed for UIU students.  
The app lets you enter completed credits, current CGPA, and current semester courses with their credits and grade points, then calculates:

- 📌 Current semester **GPA**
- 📌 Updated overall **CGPA**

It also includes a separate **grading scale window** showing letter grades, grade points, and mark ranges.

---

## ✨ Features

- Input for:
  - **Completed credits** so far  
  - **Current CGPA**
- Dynamic course rows:
  - Start with 1 course, add up to **8 courses**
  - **Add** / **Remove** course buttons  
- For each course:
  - Select **credit** (1–4)  
  - Select **grade point** (4.00–1.00) from a dropdown  
- Calculates:
  - **Semester GPA** (based on selected courses)  
  - **New CGPA** (combining previous CGPA + new semester)
- Input validation:
  - Ensures CGPA is between **0.00** and **4.00**
  - Ensures credits are whole numbers
  - Warns if any course credit/grade is left as `Select`
- **Grading** button:
  - Opens a separate window showing:
    - Letter grade (A, A-, B+, …, D)
    - Grade point (4.00–1.00)
    - Marks range (e.g., 90–100, 86–89, etc.)

---

## 📁 Project Structure

uiu-cgpa-calculator/
│
├── Main.java          # Entry point – launches the Calculator window
├── Calculator.java    # Main CGPA/GPA calculator GUI and logic
├── Grading.java       # Separate window showing grade–point–marks table
└── README.md          # Project documentation

## ▶️ How to Run

You have two main options to run this application: using the terminal or an Integrated Development Environment (IDE).

### Option 1 – Using Terminal (Command Line)

1.  **Navigate** to the `uiu-cgpa-calculator` folder in your terminal.
2.  **Compile** all the Java source files using the Java compiler:

    ```bash
    javac *.java
    ```

3.  **Run** the application by executing the `Main` class:

    ```bash
    java Main
    ```

### Option 2 – Using an IDE (IntelliJ / Eclipse / NetBeans)

1.  **Create** a new **Java project** in your IDE.
2.  **Copy** the following source files into the project's `src` folder (or equivalent source directory):
    * `Main.java`
    * `Calculator.java`
    * `Grading.java`
3.  **Set** `Main` as the **main class** or the primary run configuration for the project.
4.  **Run** the project directly from the IDE.

---

## 🌱 Future Improvements

I plan to add the following features to enhance the calculator's functionality:

* Add support for **Retake / Improvement** courses.
* Implement **Per-semester breakdown and history** tracking.
* Allow **saving and loading** course data (e.g., to a file).
* Add **UI themes** or a **Dark Mode** for a better user experience.

---

## 🙋‍♂️ Author

**Sadid Ahmed (litch07)**
