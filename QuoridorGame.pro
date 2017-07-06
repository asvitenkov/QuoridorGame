#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T21:50:38
#
#-------------------------------------------------

QT       += core

QT       -= gui



#DEFINES += NO_DEBUG_PRINT QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT



TARGET = QuoridorGame
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    structures.cpp \
    datautils.cpp \
    gamedatahash.cpp

HEADERS += \
    structures.h \
    datautils.h \
    defines.h \
    gamedatahash.h \
    datautilsinl.h

