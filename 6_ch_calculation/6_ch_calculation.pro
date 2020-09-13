TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        token_stream.cpp \
        variable.cpp

HEADERS += \
    std_lib_facilities.h \
    token_stream.h \
    variable.h
