TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ternary.cpp \
    strutils.cpp \
    constructed_ternary.cpp \
    calculation.cpp

win32: {
    SOURCES += getopt.c
    HEADERS += getopt.h
}

HEADERS += \
    ternary.h \
    correlation.h \
    strutils.h \
    constructed_ternary.h \
    calculation.h

QMAKE_CXXFLAGS += -std=c++11 #-DGRAPH_SEQUENCES #-DVERBOSE_DEBUG
