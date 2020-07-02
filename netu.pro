TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -liw -lncursesw -ljsoncpp
CCFLAG += -W -Wall -Wextra -pedantic

SOURCES += \
        main.cpp \
        netutility.cpp

HEADERS += \
    colors.h \
    netutility.h
