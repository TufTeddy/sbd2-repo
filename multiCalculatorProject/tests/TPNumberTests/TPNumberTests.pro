QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

VPATH += ../../multicalculatorapp

INCLUDEPATH += ../../multicalculatorapp

SOURCES +=  tst_tpnumbertest.cpp \
    ../../multicalculatorapp/tpnumber.cpp

HEADERS += \
    ../../multicalculatorapp/tpnumber.h

