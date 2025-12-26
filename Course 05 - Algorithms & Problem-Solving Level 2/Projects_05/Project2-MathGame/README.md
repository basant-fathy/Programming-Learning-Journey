# Math-Quiz-Game
A console-based Math Quiz game written in C++. Supports multiple difficulty levels, operation types, score tracking, colored feedback, and a final pass/fail result.

# ➕➖✖️➗ Math Quiz Game (C++)

This is an interactive **console-based Math Quiz game** written in **C++**.  
The player answers a set of randomly generated math questions based on selected **difficulty level** and **operation type**, with instant feedback and a final result summary.

---

## 🎮 How It Works

- The player chooses:
  - Number of questions (1–10)
  - Question difficulty:
    - Easy
    - Medium
    - Hard
    - Mixed
  - Operation type:
    - Addition
    - Subtraction
    - Multiplication
    - Division
    - Mixed
- For each question:
  - Two random numbers are generated based on the difficulty level.
  - A math operation is applied.
  - The player enters their answer.
  - The program checks the answer and gives instant feedback:
    - 🟢 Green → Correct answer
    - 🔴 Red → Wrong answer (with correct result shown)
- After all questions, the final results are displayed.

---

## 🔧 Features

- Customizable number of questions (1–10).
- Multiple difficulty levels (Easy, Medium, Hard, Mixed).
- Multiple operation types (Add, Sub, Mul, Div, Mixed).
- Random question generation.
- Tracks correct and wrong answers.
- Final **PASS / FAIL** result.
- Color-based feedback for each answer.
- Replay option after finishing the quiz.

---

## 🧠 Technical Concepts Used

- **Enumerations (`enum`)**: For question levels and operation types.
- **Structures (`struct`)**: To organize questions and quiz data.
- **Random number generation**: For questions and mixed operations.
- **Functions**: For modular design (generate questions, validate answers, show results).
- **Arrays**: To store multiple questions.
- **Console color formatting**: Using `system("color")` for visual feedback.
- **Input validation**: Ensures correct user inputs.

---

## 🖥️ How to Compile and Run

1. Make sure you have a C++ compiler installed (e.g. `g++`).
2. Save the file as `Math-Quiz-Game.cpp`.
3. Compile and run:
___

## 🎥 Demo Video
- [Watch on LinkedIn](https://www.linkedin.com/posts/bassant-fathy-575582388_%D9%83%D9%84-%D9%85%D8%B4%D8%B1%D9%88%D8%B9-%D8%A3%D8%AB%D9%86%D8%A7%D8%A1-%D8%B1%D8%AD%D9%84%D8%A9-%D8%AA%D8%B9%D9%84%D9%85-%D8%A7%D9%84%D8%A8%D8%B1%D9%85%D8%AC%D8%A9-%D9%87%D9%88-%D8%AF%D8%B1%D8%B3-%D8%AC%D8%AF%D9%8A%D8%AF-activity-7386486714078490624-afTI?utm_source=share&utm_medium=member_desktop&rcm=ACoAAF97FKkBIYwEpy0feW2XgwBRrZ2baraYufs)
