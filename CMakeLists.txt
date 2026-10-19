cmake_minimum_required(VERSION 3.16)
project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

# app.rc gives the .exe file itself an icon (shown in File Explorer, taskbar shortcut, etc.)
if(WIN32)
    enable_language(RC)
    set(APP_ICON_RESOURCE app.rc)
endif()

add_executable(pomodoro
    WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
    worker.cpp
    worker.h
    icon.qrc
    sounds.qrc
    ${APP_ICON_RESOURCE}
)

target_link_libraries(pomodoro PRIVATE Qt6::Widgets Qt6::Multimedia)