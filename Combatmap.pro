#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T18:32:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Combatmap
TEMPLATE = app


SOURCES += main.cpp\
        combatmap.cpp \
    settings.cpp \
    combatparticipant.cpp \
    clickablelabel.cpp \
    playerpopup.cpp

HEADERS  += combatmap.h \
    settings.h \
    combatparticipant.h \
    clickablelabel.h \
    playerpopup.h

FORMS    += combatmap.ui \
    settings.ui \
    playerpopup.ui
