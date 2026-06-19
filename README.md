# ATM Simulation System (C++)

A standalone, console-based ATM Simulation application developed in C++ using the Functional Programming paradigm. This project focuses on simulating user-facing automated teller machine workflows, user authentication, and real-time transaction tracking.

## ✨ Core Features

* **User Authentication:** Simulates ATM card logging with secure credentials validation before accessing banking operations.
* **Quick Withdrawal:** Provides pre-defined standard withdrawal shortcuts for common cash amounts to enhance user experience.
* **Normal Withdrawal:** Allows customized transaction amounts with strict real-time verification against the client's current account balance.
* **Live Balance Tracking:** Instantly displays real-time account balances after each financial operation.

## 📁 Project Files

This repository contains the clean source files required to run the application:

* `ATMSystemCourse8.cpp`: The primary C++ source file containing the complete ATM system logic.
* `ClientsFile.txt`: The text database used to store, verify, and update client account data and balances.

## 🛠️ Concepts & Skills Demonstrated

* **Functional Paradigm:** Designing predictable system behaviors using clean procedural and modular C++ functions.
* **Input Validation:** Implementing continuous boundary and type-checking to prevent system logic crashes on invalid user entries.
* **File I/O Handling:** Reading, parsing, and dynamically updating text-based records to keep balances persistent.

## 🚀 How to Run the Project

This repository contains the clean source code and its data file. You can easily compile and run it using any standard C++ compiler (like `g++`).

1. Clone the repository to your local machine.
2. **Important:** Make sure both `ATMSystemCourse8.cpp` and `ClientsFile.txt` are placed in the exact same folder.
3. Open your terminal or command prompt in that directory.
4. Compile the code using the following command:

```bash
g++ ATMSystemCourse8.cpp -o ATMSystem
```

5. Run the executable:

   * On Windows: `ATMSystem.exe`
   * On Linux/Mac: `./ATMSystem`

---

## 🧑‍💻 Developer

Developed by **Mohammad Abdeqlader**.
