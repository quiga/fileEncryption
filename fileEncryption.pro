#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T12:50:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileEncryption
CONFIG   += console
CONFIG   += crypto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    typetext.cpp \
    crypto.cpp

HEADERS  += mainwindow.h \
    abstractTypes.h \
    typetext.h \
    crypto.h

FORMS    += \
    crypto.ui

LIBS += -L /usr/lib/ -lqca
