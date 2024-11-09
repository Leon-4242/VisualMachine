QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = Func
TEMPLATE = app

SOURCES += \
    ../../HSE_less_MSU/4_task/Bezie.cpp \
    DrawArea.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../HSE_less_MSU/4_task/Bezie.h \
    ../../HSE_less_MSU/4_task/R2Geometry.h \
    DrawArea.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
