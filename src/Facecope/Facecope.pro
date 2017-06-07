#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T01:54:14
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Facecope
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14


INCLUDEPATH+=ImageProcessing/   \
            include/

SOURCES += main.cpp\
        FMainWindow.cpp \
    ImageProcessing/Utils.cpp \
    ImageProcessing/FPerson.cpp \
    ImageProcessing/FImage.cpp \
    ImageProcessing/FFaceRecognizer.cpp \
    ImageProcessing/FFaceDetector.cpp \
    ImageProcessing/FFaceArea.cpp \
    StartMenuForm.cpp \
    FPicture.cpp \
    FileBrowserForm.cpp \
    ImageProcessing/FPicruresModel.cpp

HEADERS+=include/FMainWindow.h  \
    ImageProcessing/Utils.h \
    ImageProcessing/FPerson.h \
    ImageProcessing/FImage.h \
    ImageProcessing/FFaceRecognizer.h \
    ImageProcessing/FFaceDetector.h \
    ImageProcessing/Facecope.h \
    ImageProcessing/FFaceArea.h \
    StartMenuForm.h \
    FPicture.h \
    FileBrowserForm.h \
    ImageProcessing/FPicruresModel.h


FORMS    += uis/FMainWindow.ui  \
    StartMenuForm.ui \
    FImage.ui \
    FileBrowserForm.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
