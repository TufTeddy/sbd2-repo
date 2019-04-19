QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

VPATH += ../../multicalculatorapp

INCLUDEPATH += ../../multicalculatorapp

SOURCES +=  tst_proctests.cpp

SOURCES +=  tst_proctests.cpp \
    ../../multicalculatorapp/tproc.cpp \
    ../../multicalculatorapp/tfrac.cpp

HEADERS += \
    ../../multicalculatorapp/tproc.h \
    ../../multicalculatorapp/tfrac.h
