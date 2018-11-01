include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11 sql
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_testclass.h

SOURCES += \
        main.cpp
