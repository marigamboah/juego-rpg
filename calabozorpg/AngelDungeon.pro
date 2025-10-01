QT += widgets core gui
CONFIG += c++17
TEMPLATE = app
TARGET = AngelDungeon

INCLUDEPATH += engine

SOURCES +=         main.cpp         ui/mainwindow.cpp         engine/items.cpp         engine/character.cpp         engine/enemy.cpp         engine/floor.cpp         engine/game.cpp         engine/save.cpp

HEADERS +=         ui/mainwindow.h         engine/types.h         engine/items.h         engine/character.h         engine/enemy.h         engine/floor.h         engine/game.h         engine/save.h

FORMS +=         ui/mainwindow.ui
