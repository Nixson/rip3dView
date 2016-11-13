#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T19:44:10
#
#-------------------------------------------------

QT       += core gui widgets multimedia printsupport network

TARGET = rip3p
TEMPLATE = app

SOURCES += main.cpp\
        rip3d.cpp \
    qcustomplot.cpp \
    work.cpp \
    twork.cpp \
    tmath.cpp \
    rcontrol.cpp \
    fft.cpp \
    plotgl.cpp \
    scobject.cpp

HEADERS  += rip3d.h \
    qcustomplot.h \
    work.h \
    twork.h \
    tmath.h \
    rcontrol.h \
    fft.h \
    plotgl.h \
    scobject.h

FORMS    += rip3d.ui

RESOURCES += \
    res.qrc

target.path = ..
INSTALLS += target

DESTDIR = ..
