include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_testsclass.h \
    stringpolindrome.h

SOURCES += \
        main.cpp \
    stringpolindrome.cpp
