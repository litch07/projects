# Banking System – Java OOP Project

A console-based banking system built using **Object-Oriented Programming (OOP)** in Java.  
This project demonstrates user management, admin control, transactions, activity logs, inheritance, and polymorphism.

---

## ✨ Features

### 👤 User Features
- Sign Up (with age validation – must be 18+)
- Sign In (username + password authentication)
- View balance
- Deposit money
- Withdraw money (with insufficient balance check)
- View personal transaction logs
- Secure logout system

### 🛠 Admin Features
- Admin login using predefined credentials  
  (`username: admin`, `password: admin`)
- View all registered users
- Search users by username
- Remove users
- View **all activity logs** (system-wide)
- Admin logout

### 🧾 Logging System
Two types of logs are maintained:

1. **ActivityLog**
   - Tracks high-level system activities  
     e.g., user creation, login/logout, admin actions

2. **TransactionLog**
   - Tracks financial operations  
     e.g., deposit, withdrawal, new balance

---

## 🧱 Project Structure

```text
banking-system-java/
│
├── Main.java              # Main menu and program flow
├── Person.java            # Base class for User and Admin
├── User.java              # User account + transactions
├── Admin.java             # Admin functionality
├── ActivityLog.java       # Tracks actions like user login/signup/delete
├── TransactionLog.java    # Tracks deposits & withdrawals
└── README.md              # Project documentation
```

## ▶️ How to Run

You can run this application using the terminal or an integrated development environment (IDE).

### Option 1: Compile & Run Using Terminal

1.  **Navigate to the folder:** Ensure you are inside the `banking-system-java` folder.
2.  **Compile all `.java` files:**
    ```bash
    javac *.java
    ```
3.  **Run the program:**
    ```bash
    java Main
    ```

### Option 2: Run Using an IDE (IntelliJ / Eclipse / NetBeans)

1.  Create a new **Java project** in your preferred IDE.
2.  **Copy all `.java` files** into the project’s **`src`** folder.
3.  Set the **`Main`** class as the run configuration.
4.  Run the application.

---

## 🧠 OOP Concepts Used

This project demonstrates several core **Object-Oriented Programming (OOP)** principles:

* **Inheritance:** Classes like `User` and `Admin` extend the base class $\mathbf{Person}$.
* **Encapsulation:** Data is protected and stored within objects (e.g., account details within the $\mathbf{User}$ class).
* **Method Overriding:** The $\mathbf{displayDetails()}$ method is customized in the $\mathbf{User}$ class.
* **Composition:** The $\mathbf{User}$ class "has-a" relationship with a list of $\mathbf{TransactionLogs}$.
* **Polymorphism:** Common fields and methods are reused and implemented across different classes through inheritance.
* **Clean Separation of Classes:** Ensures better maintainability and modular design.

---

## 🌱 Future Improvements

These are potential enhancements for the project:

* Add **file/database saving** so user data persists after the program exits.
* Implement **password encryption** for enhanced security.
* Add an **interest calculation** or **loan module**.
* Create a **GUI version** using **Java Swing** or **JavaFX**.
* Implement a **username uniqueness check** upon account creation.

---

## 🙋‍♂️ Author

**Sadid Ahmed (litch07)**
