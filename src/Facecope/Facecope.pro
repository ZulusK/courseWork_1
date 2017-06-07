#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T01:54:14
#
#-------------------------------------------------

QT       += core gui
QT      +=concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Facecope
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14


INCLUDEPATH+=ImageProcessing/   \
            include/

SOURCES += main.cpp\
    ImageProcessing/Utils.cpp \
    ImageProcessing/FPerson.cpp \
    ImageProcessing/FImage.cpp \
    ImageProcessing/FFaceRecognizer.cpp \
    ImageProcessing/FFaceDetector.cpp \
    ImageProcessing/FFaceArea.cpp \
    FPicture.cpp \
    FMainWindow.cpp \
    FWorkingWidget.cpp \
    FIcon.cpp \
    FImageThumbModel.cpp

HEADERS+=\
    FPicture.h \
    FMainWindow.h \
    FWorkingWidget.h \
    FIcon.h \
    FImageThumbModel.h

FORMS    +=  \
    FMainWindow.ui \
    FWorkingWidget.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv