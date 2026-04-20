# 🔍 Duplicate File Finder (C++)

A simple tool to detect and manage duplicate files based on **actual file content** instead of filenames.

---

## 📌 What it does

* Scans a given directory (including subfolders)
* Identifies duplicate files using **SHA-256 hashing**
* Groups files with identical content
* Optionally deletes duplicate files (keeps one copy)

---

## ⚙️ How it works (high-level)

* Uses a custom **HashMap (chaining + rehashing)** to store file hashes
* Traverses directories using a **DFS-based N-ary tree structure**
* Reads files in **binary mode** and generates hash using OpenSSL
* Tracks duplicate entries efficiently using indexed buckets

---

## 🧠 Concepts Used

* Data Structures:

  * Hash Map (custom implementation)
  * Linked List
  * N-ary Tree

* Algorithms:

  * Depth First Search (DFS)
  * Hashing

* Systems:

  * File handling (binary I/O)
  * Directory traversal
  * SHA-256 hashing (OpenSSL)

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

## ▶️ How to Run

### Compile:

```
g++ src/*.cpp -Iinclude -lssl -lcrypto -o duplicate_finder
```

### Run:

```
./duplicate_finder
```

Then enter the directory path when prompted.

---

## ⚠️ Notes

* Duplicate detection is based on **content**, not filenames
* Deletion is optional and requires confirmation
* Make sure OpenSSL is properly installed and linked

---

## 📸 Example Output
---
<img width="1728" height="850" alt="image" src="https://github.com/user-attachments/assets/edfefe4f-a4f7-433d-bb21-1b4c3da8efac" />


---
<img width="1701" height="481" alt="image" src="https://github.com/user-attachments/assets/8f4df26d-477d-46f2-9681-0cdafe0a20b0" />


---

## 🎯 Purpose

This project was built to better understand:

* how hashing works in real scenarios
* how file systems can be traversed programmatically
* how data structures can be applied to solve practical problems

---

## 🚀 Future Improvements

* Add multithreading for faster scanning
* GUI version
* Ignore system/protected files
* Export duplicate report

---

## 👨‍💻 Author

Abdul Raffay Raja
Computer Science Student | Learning Systems & Cybersecurity

---
