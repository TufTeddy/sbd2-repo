QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

VPATH += ../../multicalculatorapp

INCLUDEPATH += ../../multicalculatorapp

SOURCES +=  tst_memtest.cpp \
    ../../multicalculatorapp/tmemory.cpp \
    ../../multicalculatorapp/tfrac.cpp

HEADERS += \
    ../../multicalculatorapp/tmemory.h \
    ../../multicalculatorapp/tfrac.h

