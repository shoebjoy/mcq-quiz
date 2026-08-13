# 🎯 MCQ Quiz — Console Quiz Game

A fully-featured **console-based Multiple Choice Quiz** application built in both **C** and **C++**. The program presents randomized questions across four knowledge categories with a scoring system, high-score persistence, and a 3-strike elimination rule.

> **Academic Project** — Daffodil International University  
> **Author:** Shoeb Mahmud Joy (ID: 192-15-13045)  
> **Advisor:** Syeda Tasmia Alvi Onika, Lecturer, Dept. of CSE

---

## 📖 Table of Contents

- [Features](#-features)
- [Quiz Categories](#-quiz-categories)
- [Game Rules](#-game-rules)
- [Project Structure](#-project-structure)
- [Building & Running](#-building--running)
  - [C Version](#c-version-mainc)
  - [C++ Version](#c-version-maincpp)
- [Architecture & Design](#-architecture--design)
- [Technical Details](#-technical-details)
  - [C Implementation](#c-implementation-mainc)
  - [C++ Implementation](#c-implementation-maincpp)
- [Score File Format](#-score-file-format)
- [Screenshots](#-screenshots)
- [License](#-license)

---

## ✨ Features

| Feature | Description |
|---|---|
| **4 Quiz Categories** | International, Bangladesh, Technology, Sports |
| **80 Unique Questions** | 20 questions per category, 10 randomly selected per quiz |
| **Randomized Selection** | Fisher-Yates shuffle ensures no question repeats within a session |
| **3-Strike Elimination** | Game ends automatically after 3 wrong answers |
| **Persistent High Score** | Top score saved to `Score.txt` across sessions |
| **Audio Feedback** | System beep on wrong answers via Windows API |
| **Performance Grading** | Automatic feedback based on final score |
| **Dual Implementations** | Clean, production-quality C and C++ versions |

---

## 📚 Quiz Categories

1. **International** — Geography, world facts, UN, oceans, rivers, deserts, etc.
2. **Bangladesh** — History, independence, culture, national symbols, landmarks
3. **Technology** — Inventions, inventors, computing history, tech milestones
4. **Sports** — Cricket, football, Olympics, Commonwealth Games, general sports trivia

Each category draws from a pool of **20 questions**. On each playthrough, **10 are randomly selected** and presented in shuffled order, so no two sessions are identical.

---

## 🕹 Game Rules

1. You have **10 questions** to answer per quiz session
2. Each question presents **4 options** — press `A`, `B`, `C`, or `D` to answer
3. Any key other than A/B/C/D is treated as a **wrong answer**
4. Each correct answer earns **5 points** (max score: **50**)
5. The game **ends immediately** after **3 incorrect** answers
6. There is **no negative marking** — wrong answers simply don't earn points

### Grading Scale

| Score Range | Feedback |
|---|---|
| 50 | Excellent!!! Keep it up :) |
| 40 – 49 | Very Good!! |
| 20 – 39 | Good! But You Need to Know More :) |
| 10 – 19 | Satisfactory Result, Study More :) |
| 0 – 9 | Your General Knowledge is Very Poor :( |

---

## 📁 Project Structure

```
mcq-quiz/
├── main.c          # C implementation (C99)
├── main.cpp        # C++ implementation (C++17)
├── Score.txt       # Auto-generated high score file (created at runtime)
└── README.md       # This file
```

---

## 🔨 Building & Running

> **Platform:** Windows (uses `<windows.h>` for `Beep()` and `<conio.h>` for `getch()` / `_getch()`)

### C Version (`main.c`)

**Using GCC (MinGW):**
```bash
gcc main.c -o quiz.exe -std=c99
./quiz.exe
```

**Using MSVC (Developer Command Prompt):**
```bash
cl main.c /Fe:quiz.exe
quiz.exe
```

### C++ Version (`main.cpp`)

**Using G++ (MinGW):**
```bash
g++ main.cpp -o quiz.exe -std=c++17
./quiz.exe
```

**Using MSVC (Developer Command Prompt):**
```bash
cl main.cpp /Fe:quiz.exe /std:c++17 /EHsc
quiz.exe
```

---

## 🏗 Architecture & Design

Both implementations follow the same **data-driven architecture** that cleanly separates the question data from the quiz logic:

```
┌─────────────────────────────────────────┐
│              main() — Menu Loop         │
│  ┌──────┬──────┬──────┬──────┬───────┐  │
│  │Start │Score │Reset │Rules │Credits│  │
│  └──┬───┴──────┴──────┴──────┴───────┘  │
│     │                                   │
│     ▼                                   │
│  ┌────────────────────────────────┐     │
│  │     Category Selection         │     │
│  │  [1] International             │     │
│  │  [2] Bangladesh                │     │
│  │  [3] Technology                │     │
│  │  [4] Sports                    │     │
│  └────────────┬───────────────────┘     │
│               │                         │
│               ▼                         │
│  ┌────────────────────────────────┐     │
│  │     run_quiz(question_bank)    │     │
│  │  • Shuffle indices             │     │
│  │  • Present 10 random Qs        │     │
│  │  • Track correct/wrong         │     │
│  │  • 3-strike elimination        │     │
│  │  • Return final score          │     │
│  └────────────┬───────────────────┘     │
│               │                         │
│               ▼                         │
│  ┌────────────────────────────────┐     │
│  │     Score Persistence          │     │
│  │  • Read Score.txt              │     │
│  │  • Compare & update if higher  │     │
│  └────────────────────────────────┘     │
└─────────────────────────────────────────┘
```

### Key Design Principles

- **Data-Driven:** All 80 questions are stored in structured arrays/vectors, not hard-coded in control flow
- **Single Quiz Engine:** One generic `run_quiz()` function handles all categories — zero code duplication
- **Proper Randomization:** Fisher-Yates shuffle (C) / `std::shuffle` with `std::mt19937` (C++) ensures uniform distribution with no repeats
- **Clean Control Flow:** `while` loops and `switch` statements replace all `goto` statements
- **Safe I/O:** `fgets()` (C) / `std::getline` (C++) instead of `gets()` to prevent buffer overflows

---

## 🔬 Technical Details

### C Implementation (`main.c`)

| Aspect | Details |
|---|---|
| **Standard** | C99 |
| **Question Storage** | `const Question[]` — static array of structs with `const char*` fields |
| **Randomization** | Custom Fisher-Yates shuffle on index array, `srand()` called once in `main()` |
| **Input** | `getch()` for single-keypress, `fgets()` for name input |
| **File I/O** | `FILE*` with `fscanf` / `fprintf` |
| **Category Dispatch** | Array of `Category` structs with function-pointer-like bank references |
| **Memory** | All data is `static const` — zero heap allocation |

**Key structs:**
```c
typedef struct {
    const char *question;
    const char *option_a, *option_b, *option_c, *option_d;
    char        answer;
} Question;

typedef struct {
    const char     *name;
    const Question *bank;
} Category;
```

---

### C++ Implementation (`main.cpp`)

| Aspect | Details |
|---|---|
| **Standard** | C++17 |
| **Question Storage** | `std::vector<Question>` with `std::array<std::string, 4>` for options |
| **Randomization** | `std::shuffle` with `std::mt19937` seeded by `std::random_device` |
| **Input** | `_getch()` for single-keypress, `std::getline` for name input |
| **File I/O** | `std::ifstream` / `std::ofstream` with RAII |
| **Category Dispatch** | `std::vector<Category>` — fully dynamic |
| **Memory** | RAII throughout; no manual `new`/`delete` |

**Key structs:**
```cpp
struct Question {
    std::string                question;
    std::array<std::string, 4> options;   // A, B, C, D
    char                       answer;

    const std::string& correct_text() const {
        return options[answer - 'A'];
    }
};

struct Category {
    std::string           name;
    std::vector<Question> bank;
};
```

**C++ Advantages over C version:**
- `std::mt19937` provides cryptographically better randomness than `rand()`
- `std::string` eliminates all buffer overflow risks
- RAII file streams guarantee cleanup on all code paths
- `std::shuffle` is a single, well-tested standard library call
- `[[nodiscard]]` on `correct_text()` catches accidental discard bugs at compile time

---

## 💾 Score File Format

The high score is persisted in `Score.txt` with a simple format:

```
PlayerName 45.00
```

- **Field 1:** Player name (single word, max 20 characters)
- **Field 2:** High score as a float (formatted to 2 decimal places)
- The file is automatically created on first play
- Score is only overwritten when a new score **meets or exceeds** the current high score

---

## 🖥 Screenshots

```
***************************** WELCOME TO Quiz Test Program 2021 *****************************

         Enter the mentioned keywords for its assigned action:

         A.Start Game
         B.High Score
         C.Reset High Score
         D.Rules
         E.Credits
         F.Exit
```

```
         Please select the subject you prefer for your quiz:

         1.International    2.Bangladesh

         3.Technology       4.Sports
```

---

## 📄 License

This project is an academic submission. Feel free to use, modify, and distribute for educational purposes.

---

<p align="center">
  <b>Built with ❤️ by Shoeb Mahmud Joy</b><br>
  Daffodil International University
</p>
