#-------------------------------------------------
#
# Project created by QtCreator 2014-10-03T12:44:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Merge
TEMPLATE = app

CONFIG +=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    recdia.cpp \
    regdia.cpp \
    widget.cpp \
    loginform.cpp \
    picgen.cpp \
    rangen.cpp \
    sharedis.cpp \
    settocenter.cpp \
    aes_ctr.cpp \
    rexh.cpp

HEADERS  += \
    mainwindow.h \
    recdia.h \
    regdia.h \
    widget.h \
    loginform.h \
    picgen.h \
    rangen.h \
    sharedis.h \
    settocenter.h \
    aes_ctr.h \
    rexh.h
LIBS += -lqrencode\
        -lcryptopp

FORMS +=
