cmake_minimum_required(VERSION 3.16)

project(Komgraf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    drawingwindow.cpp
    drawingwindow.h
    drawingcanvas.cpp
    drawingcanvas.h
)

cmake_minimum_required(VERSION 3.16)

project(Komgraf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    drawingwindow.cpp
    drawingwindow.h
    drawingcanvas.cpp
    drawingcanvas.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Komgraf
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        drawingcanvas.h drawingcanvas.cpp
        drawingwindow.h drawingwindow.cpp
    )
else()
    if(ANDROID)
        add_library(Komgraf SHARED ${PROJECT_SOURCES})
    else()
        add_executable(Komgraf ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(Komgraf PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Komgraf PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Komgraf)
endif()
