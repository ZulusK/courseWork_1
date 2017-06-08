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


INCLUDEPATH+=ImageWork/   \
            include/

SOURCES += main.cpp\
#    ImageProcessing/Utils.cpp \
#    ImageProcessing/FPerson.cpp \
#    ImageProcessing/FImage.cpp \
#    ImageProcessing/FFaceRecognizer.cpp \
#    ImageProcessing/FFaceDetector.cpp \
#    ImageProcessing/FFaceArea.cpp \
    FMainWindow.cpp \
    FWorkingWidget.cpp \
    FIcon.cpp \
    FImageThumbModel.cpp \
    FImageProxyModel.cpp \
    FHelpWidget.cpp \
    FSettingsWidget.cpp \
    Settings.cpp \
    ImageWork/FImage.cpp \
    ImageWork/FFace.cpp \
    ImageWork/FacecopeUtils.cpp \
    FImageShowDialog.cpp \
    FImageDrawAreaWidget.cpp \
    ImageWork/FFaceDetector.cpp

HEADERS+=\
    FMainWindow.h \
    FWorkingWidget.h \
    FIcon.h \
    FImageThumbModel.h \
    FImageProxyModel.h \
    FHelpWidget.h \
    FSettingsWidget.h \
    Settings.h \
    ImageWork/FImage.h \
    ImageWork/FFace.h \
    ImageWork/FacecopeTypes.h \
    ImageWork/FacecopeUtils.h \
    FImageShowDialog.h \
    FImageDrawAreaWidget.h \
    ImageWork/FFaceDetector.h

FORMS    +=  \
    FMainWindow.ui \
    FWorkingWidget.ui \
    FHelpWidget.ui \
    FSettingsWidget.ui \
    FImageShowDialog.ui \
    FImageDrawAreaWidget.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

RESOURCES += \
    ../../res/res.qrc

DISTFILES +=
