# Swing Quiz – Java OOP Project

This is a GUI-based quiz application created using **Java Swing**.  
The project demonstrates Object-Oriented Programming concepts such as classes, objects, encapsulation, event handling, and file processing.

---

## ✨ Features
- Loads questions, options, and answers from a text file  
- Displays questions one by one using a Swing UI  
- Radio button selection for multiple-choice answers  
- Next button to continue through the quiz  
- Final score display at the end  
- Fully object-oriented class structure  

---

## 📁 Project Structure
```
swing-quiz/
│
├── Main.java            # Loads questions.txt and starts the quiz
├── MainWindow.java      # GUI for displaying questions
├── StartQuiz.java       # Opening window with Start button
├── Questions.java       # Question model class
├── questions.txt        # All quiz questions, options, and correct answers
└── README.md            # Project documentation
```

---

## 📝 How the Input File Works

The `questions.txt` file follows this exact structure:

```
<Question>
<Option 1>
<Option 2>
<Option 3>
<Option 4>
<Correct Answer>
(repeat)
```

Example:
```
What would be the worst thing to say during a job interview?
"I'm allergic to hard work."
"I prefer working remotely... from bed."
"Can I take a nap first?"
"What company is this again?"
What company is this again?
```

---

## ▶️ How to Run

### 1️⃣ Compile all Java files:
```bash
javac *.java
```

### 2️⃣ Run the app:
```bash
java Main
```

---

## 🙋‍♂️ Author
Sadid Ahmed (litch07)
