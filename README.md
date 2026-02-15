# 📚 Alexandria - Library Management System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue)
![Framework](https://img.shields.io/badge/framework-Qt6-green)
![Build](https://img.shields.io/badge/build-CMake-orange)

**Alexandria** is a modern, fast, and secure desktop library management system built using **C++17** and the **Qt 6 framework**. Inspired by the Great Library of Alexandria, this project aims to streamline book inventory management and digitize library operations with a user-friendly interface.

## 🚀 Features

* **Modern Interface:** Clean, responsive, and user-friendly GUI built with Qt Widgets.
* **Secure Database:** Integrated with SQLite via the QtSql module for robust local data storage.
* **Book Management:**
    * ➕ **Add:** Create new records with Title, Author, and ISBN.
    * 📋 **List:** View the entire inventory in a real-time updating table.
    * 🗑️ **Delete:** Safely remove selected books from the database.
    * 🔄 **Status Tracking:** Monitor book availability ("Available" or "Borrowed").
* **Cross-Platform:** Designed to run seamlessly on Windows, Linux, and macOS.

## 🛠️ Tech Stack

This project is built with performance and maintainability in mind:

* **Language:** C++17
* **Framework:** Qt 6 (Core, Gui, Widgets, Sql)
* **Database:** SQLite 3 (Embedded)
* **Build System:** CMake (v3.16+)

## ⚙️ Installation & Build

Follow these steps to build and run the project on your local machine.

### Prerequisites

* A C++17 compliant compiler (GCC, Clang, or MSVC)
* [Qt 6 SDK](https://www.qt.io/download) (Required components: `Qt Sql`, `Qt Widgets`)
* [CMake](https://cmake.org/)

### Step-by-Step Guide

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/SweetRomeo/Alexandria.git](https://github.com/SweetRomeo/Alexandria.git)
    cd Alexandria
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build && cd build
    ```

3.  **Configure the project (CMake):**
    ```bash
    cmake ..
    ```
    *(Note: If CMake cannot find your Qt installation, you may need to add `-DCMAKE_PREFIX_PATH="path/to/qt/6.x.x/..."`)*

4.  **Build the application:**
    ```bash
    cmake --build .
    ```

5.  **Run:**
    Execute the generated `Alexandria` (or `Debug/Alexandria.exe` on Windows) file.
    > The application will automatically generate the `alexandria.db` database file upon the first launch.

## 📸 Screenshots

*(You can add screenshots of the application here. e.g.: `![Main Screen](docs/screenshot.png)`)*

## 🗺️ Roadmap

Future plans and upcoming features:

- [x] Basic Database Architecture (Books, Users)
- [x] Transition to Qt GUI
- [x] Book Add / Delete / List functionality
- [ ] User Management System (Add/Remove Members)
- [ ] Borrowing & Return System (Transaction Logic)
- [ ] Advanced Search & Filtering
- [ ] Statistics Dashboard

## 🤝 Contributing

Contributions are welcome!
1.  Fork the repository.
2.  Create a new feature branch (`git checkout -b feature/AmazingFeature`).
3.  Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4.  Push to the branch (`git push origin feature/AmazingFeature`).
5.  Open a Pull Request.

## 📄 License

This project is licensed under the [MIT License](LICENSE). See the `LICENSE` file for details.

---
**Developer:** [SweetRomeo](https://github.com/SweetRomeo)
