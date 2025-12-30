# Text-Based Facebook (C)

A full text-based social networking system built in C using linked lists, stacks, and dynamic memory management.

This project simulates the backend logic of a social media platform and demonstrates core concepts of systems programming, data structures, and memory safety.

---

## 🧠 System Design

The following diagram illustrates how users, friends, and posts are stored and connected internally.

> Users and friends are stored in ascending-order linked lists, while posts are implemented using a stack structure for efficient insertion and removal.

<img width="1342" height="653" alt="image" src="https://github.com/user-attachments/assets/16c8c33f-71b5-4203-9238-7f8b23bedf92" />


---

## ⚙️ Features

- User registration & authentication
- Profile management (change password)
- Friend management (add/remove friends)
- Post system using stack data structure
- Sorted linked list database for users and friends
- Interactive command-line interface
- Robust input validation and memory handling

---

## 🛠 Technologies & Concepts

- **Language:** C  
- **Core Concepts:**  
  - Linked Lists  
  - Stacks  
  - Dynamic Memory Allocation  
  - Pointers & Memory Management  
  - Modular Program Design  
  - CLI Systems

---

## 🧪 How to Run

Compile the project:

```bash
gcc -g *.c -o app
