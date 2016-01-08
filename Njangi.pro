#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T15:56:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QTPLUGIN += qsqlmysql
QT       +=printsupport

RC_FILE = appIcon.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Njangi
TEMPLATE = app

CONFIG += static

SOURCES += \ 
    add.cpp \
    deleteuser.cpp \
    edit.cpp \
    interestrate.cpp \
    loan.cpp \
    login.cpp \
    main.cpp \
    njangisystem.cpp \
    other.cpp \
    payback.cpp \
    save.cpp \
    transaction.cpp \
    useraccount.cpp \
    view.cpp \
    withdraw.cpp

HEADERS  += \
    add.h \
    deleteuser.h \
    edit.h \
    interestrate.h \
    loan.h \
    login.h \
    njangisystem.h \
    other.h \
    payback.h \
    save.h \
    transaction.h \
    useraccount.h \
    view.h \
    withdraw.h

FORMS    += \
    add.ui \
    deleteuser.ui \
    edit.ui \
    interestrate.ui \
    loan.ui \
    login.ui \
    njangisystem.ui \
    other.ui \
    payback.ui \
    save.ui \
    transaction.ui \
    useraccount.ui \
    view.ui \
    withdraw.ui

DISTFILES += \
    Njangi.pro.user \
    njangiSystem.pro.user \
    njangiSystem.pro.user.3.2-pre1\
    appIcon.rc

SUBDIRS += \
    njangiSystem.pro

RESOURCES += \
    resource.qrc

