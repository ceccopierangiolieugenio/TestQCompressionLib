#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T14:19:51
# Author:   Eugenio Parodi
#           ceccopierangiolieugenio@googlemail.com
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCompress
TEMPLATE = app

APP_NAME = "Test_Compress"

VERSION = 0.0.1
exists( .git/config ) {
      REVISION = $$system(git rev-parse HEAD)
}else{
      REVISION = "NO_GIT"
}


DEFINES += APP_NAME=\"$$APP_NAME\"
DEFINES += APP_VERSION=$$VERSION
DEFINES += APP_REVISION=$$REVISION


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SUBDIRS = lib/Qliblzma

depends = Qliblzma

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    test_lzma.cpp

HEADERS += \
        mainwindow.h \
    test_lzma.h


FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/Qliblzma/release/ -lQliblzma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/Qliblzma/debug/ -lQliblzma
else:unix: LIBS += -L$$OUT_PWD/../lib/Qliblzma/ -lQliblzma

INCLUDEPATH += $$PWD/../lib/Qliblzma/liblzma/api
DEPENDPATH += $$PWD/../lib/Qliblzma/liblzma/api
