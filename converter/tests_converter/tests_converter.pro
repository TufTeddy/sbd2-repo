QT += core testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

VPATH += ../../converter

INCLUDEPATH += ../converter

SOURCES += \ 
    tpnumbertest.cpp \
    ../converter/tpnumber.cpp\

HEADERS += \
    ../converter/tpnumber.h\

