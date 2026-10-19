# Pomodoro Timer

A simple desktop Pomodoro timer built with C++ and Qt6 Widgets.

<img width="501" height="638" alt="screenshot" src="https://github.com/user-attachments/assets/7a4885c4-c558-488c-881a-aff6eced6f2b" />


## Demo

<video src="docs/demo.mp4" controls width="400"></video>

## Features

- Work / short break / long break cycle (25 / 5 / 15 minutes)
- Start, Pause/Resume, and Reset controls
- Adjustable number of sessions before a long break, via large +/- buttons
- Progress bar for the current phase
- Custom app icon
- Dark theme UI

## Built With

- C++17
- Qt6 (Widgets module)
- CMake

## Building from source

### Requirements

- [Qt6](https://www.qt.io/download-qt-installer) (Widgets module) with MinGW 64-bit kit
- Qt Creator (recommended) or CMake 3.16+

### Steps

1. Clone this repository
2. Open `CMakeLists.txt` in Qt Creator
3. Select your Qt6 MinGW kit and configure the project
4. Build in Release mode
5. Run `windeployqt pomodoro.exe` from a Qt MinGW command prompt to bundle the required DLLs for standalone use

## How it works

- The countdown logic runs on a background `QThread` (`Worker` class) so the GUI never freezes during a session.
- `mainwindow.cpp` handles all UI wiring and button logic.
- `app.rc` / `icon.qrc` embed `icon.ico` as both the `.exe` file icon and the in-app window/taskbar icon.

## License

MIT
