# Pomodoro Timer

A simple desktop Pomodoro timer built with C++ and Qt6 Widgets.

![screenshot placeholder](docs/screenshot.png)

## Features

- Work / short break / long break cycle (25 / 5 / 15 minutes)
- Start, Pause/Resume, Stop, and Reset controls
- Adjustable number of sessions before a long break
- Progress bar for the current phase
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

## License

MIT
