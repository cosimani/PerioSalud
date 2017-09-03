#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T14:43:02
#
#-------------------------------------------------

QT       += core gui network multimedia quick qml quickwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PerioSalud
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    image.cpp \
    squircle.cpp \
    database.cpp \
    datamanager.cpp \
    error.cpp \
    login.cpp \
    registro.cpp \
    boton.cpp \
    midentista.cpp \
    comun.cpp \
    foto.cpp \
    visitas.cpp \
    miboca.cpp

HEADERS  += principal.h \
    image.hpp \
    squircle.h \
    database.hpp \
    datamanager.hpp \
    error.hpp \
    login.h \
    registro.h \
    boton.h \
    midentista.h \
    comun.h \
    foto.h \
    visitas.h \
    miboca.h

FORMS    += principal.ui \
    error.ui \
    login.ui \
    registro.ui \
    boton.ui \
    midentista.ui \
    foto.ui \
    visitas.ui \
    miboca.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    openglunderqml.qrc \
    resources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

