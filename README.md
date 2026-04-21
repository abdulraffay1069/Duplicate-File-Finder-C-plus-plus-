# 🔍 Duplicate File Finder (C++)

A system-level utility that detects duplicate files based on **content hashing**, not filenames — designed to explore how real-world tools handle file systems, hashing, and efficient data lookup.

---

## 🎯 Overview

This project scans directories recursively and identifies duplicate files by comparing their actual binary content using **SHA-256 hashing**.

Instead of relying on filenames or metadata, it ensures **accurate detection** even when files are renamed or moved.

The focus of this project is not just functionality, but understanding how:

* file systems are traversed
* hashing is applied in practice
* data structures impact performance

---

## 🚀 Features

* 📂 Recursive directory traversal (including subfolders)
* 🔐 Content-based duplicate detection using SHA-256
* 🧠 Custom-built HashMap (with chaining + rehashing)
* 🌳 DFS-based traversal using N-ary tree structure
* ⚡ Efficient grouping of duplicate files
* 🗑️ Optional deletion of duplicate files (keeps one copy)

---

## 🧠 Core Concepts & Design

### 🔹 Data Structures

* Custom **HashMap**

  * Collision handling using chaining
  * Dynamic resizing (rehashing)
* **Linked List** (for bucket storage)
* **N-ary Tree** (for directory traversal)

---

### 🔹 Algorithms

* **Depth First Search (DFS)**
  Used to traverse directory structure completely

* **Hashing (SHA-256)**
  Ensures reliable and collision-resistant file comparison

---

### 🔹 System-Level Concepts

* Binary file reading
* File system traversal
* Memory management using pointers
* External library integration (OpenSSL)

---

## ⚡ Efficiency

* Hash-based lookup provides **~O(1)** average access time
* DFS ensures full directory coverage without redundancy
* Rehashing maintains performance as dataset size grows
* Duplicate tracking avoids unnecessary re-traversal

---

## 👥 Contribution

This was a team project.

**My role:**

* Designed and implemented the custom HashMap (collision handling + rehashing)
* Structured the class architecture and data flow
* Developed efficient duplicate detection logic
* Contributed to system design and integration

---

## 📂 Project Structure

```
Duplicate-File-Finder/
│
├── src/
│   ├── main.cpp
│   ├── HashMap.cpp
│   ├── HashingChecking.cpp
│   ├── List.cpp
│   ├── N_ARY_TREE.cpp
│
├── include/
│   ├── HashMap.h
│   ├── HashingChecking.h
│   ├── List.h
│   ├── N_ARY_TREE.h
│
└── README.md
```

---

## 🛠️ Requirements

* C++17 or later
* OpenSSL library

---

## ▶️ Build & Run

### Compile:

```bash
g++ src/*.cpp -Iinclude -lssl -lcrypto -o duplicate_finder
```

### Run:

```bash
./duplicate_finder
```

Then enter the directory path when prompted.

---

## 📸 Example Output

<img width="1728" height="850" src="https://github.com/user-attachments/assets/edfefe4f-a4f7-433d-bb21-1b4c3da8efac" />

<img width="1701" height="481" src="https://github.com/user-attachments/assets/8f4df26d-477d-46f2-9681-0cdafe0a20b0" />

---

## ⚠️ Notes

* Duplicate detection is based strictly on **file content**
* Deletion is optional and requires user confirmation
* OpenSSL must be correctly installed and linked

---

## 🔍 Why This Project Matters

Most duplicate detection tools rely on filenames or basic metadata.

This project demonstrates:

* how real tools ensure **accuracy using hashing**
* how **data structures directly affect performance**
* how low-level file handling works in practice

---

## 🚀 Future Improvements

* Multithreaded scanning for large directories
* GUI interface
* Filtering system (ignore system files, extensions)
* Exportable duplicate reports

---

## 👨‍💻 Author

Abdul Raffay Raja
Computer Science Student focused on Systems & Cybersecurity

---
