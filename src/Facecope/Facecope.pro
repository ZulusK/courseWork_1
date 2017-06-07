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
    FImageListModel.cpp

HEADERS+= \
    ImageProcessing/Utils.h \
    ImageProcessing/FPerson.h \
    ImageProcessing/FImage.h \
    ImageProcessing/FFaceRecognizer.h \
    ImageProcessing/FFaceDetector.h \
    ImageProcessing/Facecope.h \
    ImageProcessing/FFaceArea.h \
    FPicture.h \
    FMainWindow.h \
    FWorkingWidget.h \
    FImageListModel.h


FORMS    +=  \
    FPicture.ui \
    FMainWindow.ui \
    FWorkingWidget.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
