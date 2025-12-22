# 🚇 ITNMS - Intelligent Transport Network Management System

<div align="center">

```
  ============================================================================
  ||   _____ _______ _   _ __  __  _____                                    ||
  ||  |_   _|__   __| \ | |  \/  |/ ____|                                   ||
  ||    | |    | |  |  \| | \  / | (___                                     ||
  ||    | |    | |  | . ` | |\/| |\___ \                                    ||
  ||   _| |_   | |  | |\  | |  | |____) |                                   ||
  ||  |_____|  |_|  |_| \_|_|  |_|_____/                                    ||
  ||                                                                        ||
  ||        Intelligent Transport Network Management System                 ||
  ============================================================================
```

**A Complete Data Structures & Algorithms Implementation in C++**

[![C++11](https://img.shields.io/badge/C++-11-blue.svg?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)](.)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)
[![DS](https://img.shields.io/badge/Data%20Structures-10+-purple?style=for-the-badge)](.)
[![Algorithms](https://img.shields.io/badge/Algorithms-13+-orange?style=for-the-badge)](.)

---

*A semester project for CS 221 - Data Structures & Algorithms*  
*GIKI - Ghulam Ishaq Khan Institute*

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Data Structures Implemented](#-data-structures-implemented)
- [Algorithms Implemented](#-algorithms-implemented)
- [Installation & Usage](#-installation--usage)
- [Screenshots](#-screenshots)
- [Technical Details](#-technical-details)
- [Contributors](#-contributors)

---

## 🎯 Overview

**ITNMS** is a comprehensive transport network management system that demonstrates the practical application of fundamental data structures and algorithms. The system manages stations, routes, vehicles, passengers, and tickets while providing advanced graph algorithms for route optimization.

### 🌟 Key Highlights

- ✅ **100% Custom Implementation** - No STL containers used
- ✅ **10+ Data Structures** - All built from scratch
- ✅ **13+ Algorithms** - Including graph traversals and sorting
- ✅ **Interactive CLI** - Beautiful ASCII art interface
- ✅ **Analytics Dashboard** - Traffic predictions and insights

---

## ✨ Features

### 🏢 Station Management
- Add, delete, and view stations
- Track passenger counts per station
- Location-based organization

### 🛤️ Route Management
- Create routes between stations
- Distance tracking in kilometers
- Bidirectional route support

### 🚌 Vehicle Management
- Register vehicles with capacity
- Speed-based assignment
- Automatic fastest vehicle selection

### 🎫 Ticket & Passenger System
- FIFO queue-based passenger processing
- Automated ticket generation
- Journey tracking with station names

### 📊 Analytics & Insights
- Most crowded station analysis
- Busiest route identification
- Traffic density prediction
- Daily usage trends

### 🔬 Graph Algorithms
- **BFS** - Breadth-First Search traversal
- **DFS** - Depth-First Search traversal
- **Dijkstra's Algorithm** - Shortest path finding
- **Prim's MST** - Minimum Spanning Tree
- **Cycle Detection** - Network integrity check

### 🔍 Searching & Sorting Demos
- Linear Search & Binary Search
- Bubble, Selection, Insertion Sort
- Quick Sort, Merge Sort, Heap Sort

---

## 📁 Project Structure

```
ITNMS/
├── 📄 README.md
├── 📄 LICENSE
├── 📁 CPP/
│   ├── 📄 main.cpp              # Main application entry
│   │
│   ├── 📁 ds/                   # Data Structures
│   │   ├── array.h              # Dynamic Array
│   │   ├── linkedlist.h         # Singly Linked List
│   │   ├── stack.h              # Stack (Array-based)
│   │   ├── queue.h              # Queue (Linked List-based)
│   │   ├── hashtable.h          # Hash Table with chaining
│   │   ├── heap.h               # Min Heap
│   │   ├── trees.h              # Binary Search Tree
│   │   ├── graph.h              # Weighted Graph
│   │   ├── pair.h               # Pair utility
│   │   ├── orderedmap.h         # Ordered Map
│   │   ├── searching.h          # Search algorithms
│   │   └── sorting.h            # Sorting algorithms
│   │
│   ├── 📁 models/               # Domain Models
│   │   ├── station.h            # Station entity
│   │   ├── route.h              # Route entity
│   │   ├── vehicle.h            # Vehicle entity
│   │   ├── passenger.h          # Passenger entity
│   │   └── ticket.h             # Ticket entity
│   │
│   └── 📁 system/               # System Managers
│       ├── route_manager.h      # Station & Route operations
│       ├── vehicle_manager.h    # Vehicle operations
│       ├── ticket_manager.h     # Ticket & Queue operations
│       ├── history_manager.h    # Undo functionality
│       └── analytics.h          # Data analytics
```

---

## 🔧 Data Structures Implemented

| # | Data Structure | File | Description |
|---|----------------|------|-------------|
| 1 | **Dynamic Array** | `array.h` | Resizable array with amortized O(1) insertion |
| 2 | **Linked List** | `linkedlist.h` | Singly linked list with head/tail pointers |
| 3 | **Stack** | `stack.h` | LIFO structure for undo operations |
| 4 | **Queue** | `queue.h` | FIFO structure for passenger management |
| 5 | **Hash Table** | `hashtable.h` | Chained hashing for O(1) lookups |
| 6 | **Min Heap** | `heap.h` | Priority queue for Dijkstra's algorithm |
| 7 | **Binary Search Tree** | `trees.h` | Ordered data storage |
| 8 | **Graph** | `graph.h` | Weighted adjacency list representation |
| 9 | **Pair** | `pair.h` | Generic tuple utility |
| 10 | **Ordered Map** | `orderedmap.h` | Key-value storage with ordering |

---

## ⚡ Algorithms Implemented

### Graph Algorithms
| Algorithm | Complexity | Use Case |
|-----------|------------|----------|
| BFS | O(V + E) | Level-order traversal |
| DFS | O(V + E) | Deep exploration |
| Dijkstra | O((V + E) log V) | Shortest path |
| Prim's MST | O(E log V) | Minimum spanning tree |
| Cycle Detection | O(V + E) | Network validation |

### Sorting Algorithms
| Algorithm | Best | Average | Worst |
|-----------|------|---------|-------|
| Bubble Sort | O(n) | O(n²) | O(n²) |
| Selection Sort | O(n²) | O(n²) | O(n²) |
| Insertion Sort | O(n) | O(n²) | O(n²) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) |

### Searching Algorithms
| Algorithm | Complexity | Requirement |
|-----------|------------|-------------|
| Linear Search | O(n) | None |
| Binary Search | O(log n) | Sorted array |

---

## 🚀 Installation & Usage

### Prerequisites
- C++11 compatible compiler (g++, clang++, MSVC)
- Windows / Linux / macOS

### Compilation

```bash
# Navigate to CPP directory
cd CPP

# Compile with g++
g++ -std=c++11 -o transport_system main.cpp

# Run the application
./transport_system.exe    # Windows
./transport_system        # Linux/macOS
```

### Quick Start

1. **Add Stations** - Create transport network nodes
2. **Add Routes** - Connect stations with distances
3. **Register Vehicles** - Add transport vehicles
4. **Process Passengers** - Queue and issue tickets
5. **Run Analytics** - View insights and predictions
6. **Explore Algorithms** - Test graph and sorting demos

---

## 📸 Screenshots

### Main Menu
```
  ============================================================================
  ||   _____ _______ _   _ __  __  _____                                    ||
  ||  |_   _|__   __| \ | |  \/  |/ ____|                                   ||
  ||    | |    | |  |  \| | \  / | (___                                     ||
  ||    | |    | |  | . ` | |\/| |\___ \                                    ||
  ||   _| |_   | |  | |\  | |  | |____) |                                   ||
  ||  |_____|  |_|  |_| \_|_|  |_|_____/                                    ||
  ||                                                                        ||
  ||        Intelligent Transport Network Management System                 ||
  ||                          Version 1.0                                   ||
  ============================================================================

  ==================== MAIN MENU ====================
  ||                                                ||
  ||   1. Manage Stations                           ||
  ||   2. Manage Routes                             ||
  ||   3. Manage Vehicles                           ||
  ||   4. Manage Passengers & Tickets               ||
  ||   5. View System Information                   ||
  ||   6. Graph Algorithms & Analysis               ||
  ||   7. History & Undo                            ||
  ||   8. Searching & Sorting Demos                 ||
  ||   9. Exit                                      ||
  ====================================================
```

---

## 🔬 Technical Details

### Design Principles
- **No STL Containers** - All data structures implemented from scratch
- **Header-Only** - Single compilation unit for simplicity
- **Modular Architecture** - Separated concerns (models, DS, managers)
- **Memory Management** - Proper allocation/deallocation

### Constraints Met
- ✅ Custom Dynamic Array (replaces `std::vector`)
- ✅ Custom Linked List (replaces `std::list`)
- ✅ Custom Hash Table (replaces `std::unordered_map`)
- ✅ Custom Queue (replaces `std::queue`)
- ✅ Custom Stack (replaces `std::stack`)
- ✅ Custom Heap (replaces `std::priority_queue`)

---

## 👨‍💻 Contributors

| Name | Role |
|------|------|
| **Misbah Ullah** | Developer |

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Made with ❤️ for CS 221 - Data Structures & Algorithms**

*GIKI - Ghulam Ishaq Khan Institute of Engineering Sciences and Technology*

---

⭐ Star this repository if you found it helpful!

</div>
