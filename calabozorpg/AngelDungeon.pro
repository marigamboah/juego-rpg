QT += widgets multimedia
CONFIG += c++17

TEMPLATE = app
TARGET = AngelDungeon

INCLUDEPATH += .

# Headers
HEADERS += \
    engine/types.h \
    engine/character.h \
    engine/enemy.h \
    engine/items.h \
    engine/floor.h \
    engine/game.h \
    engine/save.h \
    ui/mainwindow.h

# Sources
SOURCES += \
    engine/character.cpp \
    engine/enemy.cpp \
    engine/floor.cpp \
    engine/game.cpp \
    engine/save.cpp \
    ui/mainwindow.cpp \
    main.cpp

# Forms (Qt Designer)
FORMS += \
    ui/mainwindow.ui

# Recursos (QRC)
RESOURCES += \
    resources.qrc

# Recomendado: ver warnings de APIs obsoletas (opcional)
DEFINES += QT_DEPRECATED_WARNINGS
