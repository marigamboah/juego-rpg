cmake_minimum_required(VERSION 3.16)

project(calabozorpg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Definimos los archivos de cabecera en la carpeta 'headers'
set(HEADERS
    headers/mainwindow.h
    headers/jugador.h
    headers/enemigo.h
)

# Definimos los archivos de implementación en la carpeta 'sources'
set(SOURCES
    sources/main.cpp
    sources/mainwindow.cpp
    sources/jugador.cpp
    sources/enemigo.cpp
)

# Definimos el archivo de interfaz de usuario en la carpeta 'forms'
set(FORMS
    forms/mainwindow.ui
)

# Define the target name and source files explicitly
qt_add_executable(calabozorpg
    main.cpp
    mainwindow.cpp
    mainwindow.h
    jugador.cpp
    jugador.h
    enemigo.cpp
    enemigo.h
    mainwindow.h mainwindow.cpp mainwindow.ui
)

# Enlazamos las librerías necesarias
target_link_libraries(calabozorpg PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(calabozorpg)
endif()
