QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

VPATH += ../../multicalculatorapp

INCLUDEPATH += ../../multicalculatorapp

SOURCES +=  tst_ctrlrtest.cpp\
    ../../multicalculatorapp/tctrl.cpp\
    ../../multicalculatorapp/tfrac.cpp

HEADERS += \
    ../../multicalculatorapp/tctrl.h \
    ../../multicalculatorapp/tfrac.h

