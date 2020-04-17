RC_ICONS = logo.ico
RC_FILE = icon.rc


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql
CONFIG +=console
TARGET = ticket
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        details.cpp \
        mainwindow.cpp \
        main.cpp \
        paysucc.cpp \
        ticket.cpp \

HEADERS += \
        details.h \
        mainwindow.h \
        paysucc.h \
        ticket.h

FORMS += \
        details.ui \
        mainwindow.ui \
        paysucc.ui \
        ticket.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/huoche.png \
    img/huochezhalan.png \
    img/logo.png

RESOURCES += \
    resource.qrc
