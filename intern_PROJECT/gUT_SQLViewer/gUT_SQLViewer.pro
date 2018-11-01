include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11 sql
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt
QT     += core gui sql widgets

HEADERS += \
        tst_testclass.h \
    ../SQLViewer/database.h

SOURCES += \
        main.cpp \
    ../SQLViewer/database.cpp
