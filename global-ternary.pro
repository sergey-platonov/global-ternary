TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ternary.cpp \
    strutils.cpp \
    constructed_ternary.cpp \
    calculation.cpp

HEADERS += \
    ternary.h \
    correlation.h \
    strutils.h \
    constructed_ternary.h \
    calculation.h

QMAKE_CXXFLAGS += -std=c++11 #-DGRAPH_SEQUENCES #-DVERBOSE_DEBUG
