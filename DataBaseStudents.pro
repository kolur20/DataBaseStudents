#-------------------------------------------------
#
# Project created by QtCreator 2016-06-11T14:37:59
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBaseStudents
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialog.cpp \
    newteacherdialog.cpp

HEADERS  += mainwindow.h \
    database.h \
    dialog.h \
    newteacherdialog.h

FORMS    += mainwindow.ui \
    dialog.ui \
    newteacherdialog.ui
