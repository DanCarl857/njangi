#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T12:10:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QTPLUGIN += qsqlmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = njangiSystem
TEMPLATE = app


SOURCES += main.cpp\
        njangisystem.cpp \
    login.cpp \
    useraccount.cpp \
    deleteuser.cpp \
    interestrate.cpp \
    loan.cpp \
    other.cpp \
    payback.cpp \
    save.cpp \
    transaction.cpp \
    withdraw.cpp \
    view.cpp \
    add.cpp \
    edit.cpp

HEADERS  += njangisystem.h \
    login.h \
    useraccount.h \
    deleteuser.h \
    interestrate.h \
    loan.h \
    other.h \
    payback.h \
    save.h \
    transaction.h \
    withdraw.h \
    view.h \
    add.h \
    edit.h

FORMS    += njangisystem.ui \
    login.ui \
    useraccount.ui \
    deleteuser.ui \
    interestrate.ui \
    loan.ui \
    other.ui \
    payback.ui \
    save.ui \
    transaction.ui \
    withdraw.ui \
    view.ui \
    add.ui \
    edit.ui

OTHER_FILES += \
    njangiSystem.pro.user

RESOURCES += \
    resource.qrc
