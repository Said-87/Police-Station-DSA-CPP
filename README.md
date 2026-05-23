# Police Station Management System (DSA in C++)

A highly efficient, console-based **Police Station Management System** developed in C++. This project focuses on utilizing optimal **Data Structures and Algorithms (DSA)** to handle emergency dispatches, criminal records, and rapid case lookups with minimal time complexity.

---

## 🛠️ Data Structures Implemented

### 1. Priority Queue (Max-Heap) — Emergency Dispatch
* **Purpose:** Handles incoming emergency calls or complaints.
* **Logic:** Not all crimes carry the same urgency. Cases are assigned a priority level (e.g., Critical vs. Minor Theft). High-priority emergencies are automatically pushed to the front of the queue for immediate officer dispatch.

### 2. Doubly Linked List — Criminal & Suspect Records
* **Purpose:** Manages active records of criminals and suspects in custody.
* **Logic:** Allows dynamic memory allocation where records can be easily inserted or removed (e.g., when a suspect is released or transferred) in $O(1)$ time complexity without shifting elements like a traditional array.

### 3. Hash Map (`std::unordered_map`) — Record Lookups
* **Purpose:** Instant searching for Officer Badges or Case IDs.
* **Logic:** Optimizes search operations from $O(N)$ to an average of $O(1)$ time complexity, ensuring that desk officers can pull up a case file instantly by entering a unique ID.

### 4. Queue (FIFO) — Citizen Complaints
* **Purpose:** Manages standard, non-emergency citizen complaints.
* **Logic:** Operates on a First-In, First-Out basis to ensure fair, chronological processing of paperwork.

---

## 📂 Core Components & System Flow
* **`Case` Entity:** Stores Case ID, Description, Priority Level, and Status (Open/Closed).
* **`Officer` Entity:** Tracks Badge Number, Name, Rank, and Availability Status.
* **`Station Manager`:** The central controller executing the algorithms for dispatching officers, logging complaints, and updating records.

---

## 🚀 How to Run the Project

### Prerequisites
Ensure you have a C++ compiler installed (GCC/G++ or Clang).

### Execution Steps
1. Clone the repository to your local machine:
   ```bash
   git clone [https://github.com/Said-87/Police-Station-DSA-CPP.git](https://github.com/Said-87/Police-Station-DSA-CPP.git)
