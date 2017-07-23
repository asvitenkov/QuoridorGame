#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T21:50:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#DEFINES += NO_DEBUG_PRINT QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT



TARGET = QuoridorGame
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    structures.cpp \
    datautils.cpp \
    gamedatahash.cpp \
    searchalg.cpp \
    playgroundwidget.cpp \
    gamealg.cpp

HEADERS += \
    structures.h \
    datautils.h \
    defines.h \
    gamedatahash.h \
    datautilsinl.h \
    searchalg.h \
    playgroundwidget.h \
    gamealg.h

FORMS += \
    playgroundwidget.ui

