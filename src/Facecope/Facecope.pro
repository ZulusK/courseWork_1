#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T01:54:14
#
#-------------------------------------------------

QT       += core gui
QT      +=concurrent
QT      +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Facecope
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14


INCLUDEPATH+=ImageWork/         \
            include/            \
            widgets/include     \
            models/include      \
            ImageWork/include   \

SOURCES +=\
    main.cpp                            \
    widgets/FMainWindow.cpp             \
    widgets/FWorkingWidget.cpp          \
    widgets/FHelpWidget.cpp             \
    widgets/FSettingsWidget.cpp         \
    widgets/FImageShowDialog.cpp        \
    widgets/FImageDrawAreaWidget.cpp    \
    models/FImageThumbModel.cpp         \
    models/FImageProxyModel.cpp         \
    models/FFaceModel.cpp               \
    ImageWork/FImage.cpp                \
    ImageWork/FFace.cpp                 \
    ImageWork/FacecopeUtils.cpp         \
    ImageWork/FFaceDetector.cpp         \
    ImageWork/FFaceRecognizer.cpp       \
    Settings.cpp                        \
    FDatabaseDriver.cpp \
    widgets/FSetFaceInfoDialog.cpp

HEADERS+=\
    widgets/include/FMainWindow.h           \
    widgets/include/FWorkingWidget.h        \
    widgets/include/FHelpWidget.h           \
    widgets/include/FSettingsWidget.h       \
    widgets/include/FImageShowDialog.h      \
    widgets/include/FImageDrawAreaWidget.h  \
    models/include/FFaceModel.h             \
    models/include/FImageThumbModel.h       \
    models/include/FImageProxyModel.h       \
    ImageWork/include/FImage.h              \
    ImageWork/include/FFace.h               \
    ImageWork/include/FacecopeTypes.h       \
    ImageWork/include/FacecopeUtils.h       \
    ImageWork/include/FFaceDetector.h       \
    ImageWork/include/FFaceRecognizer.h     \
    Settings.h                              \
    FDatabaseDriver.h \
    widgets/FSetFaceInfoDialog.h

FORMS    +=  \
    widgets/uis/FMainWindow.ui \
    widgets/uis/FWorkingWidget.ui \
    widgets/uis/FHelpWidget.ui \
    widgets/uis/FSettingsWidget.ui \
    widgets/uis/FImageShowDialog.ui \
    widgets/uis/FImageDrawAreaWidget.ui \
    widgets/FSetFaceInfoDialog.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

RESOURCES += \
    ../../res/res.qrc

DISTFILES +=
