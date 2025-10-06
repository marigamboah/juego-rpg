
QT += widgets
CONFIG += c++17

HEADERS += \
    engine/types.h \
    engine/character.h \
    engine/enemy.h \
    engine/items.h \
    engine/floor.h \
    engine/game.h \
    engine/save.h \
    ui/mainwindow.h

SOURCES += \
    engine/character.cpp \
    engine/enemy.cpp \
    engine/items.cpp \
    engine/floor.cpp \
    engine/game.cpp \
    engine/save.cpp \
    ui/mainwindow.cpp \
    main.cpp

FORMS += \
    ui/mainwindow.ui


