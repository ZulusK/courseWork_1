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


INCLUDEPATH+=FacecopeCore/         \
            include/            \
            widgets/include     \
            models/include      \
            FacecopeCore/include   \

SOURCES +=\
    main.cpp                            \
    widgets/FMainWindow.cpp             \
    widgets/FWorkingWidget.cpp          \
    widgets/FHelpWidget.cpp             \
    widgets/FSettingsWidget.cpp         \
    widgets/FImageShowDialog.cpp        \
    widgets/FImageDrawAreaWidget.cpp    \
    widgets/FSetFaceInfoDialog.cpp      \
    models/FImageProxyModel.cpp         \
    models/FFaceModel.cpp               \
    FacecopeCore/FImage.cpp             \
    FacecopeCore/FFace.cpp              \
    FacecopeCore/FacecopeUtils.cpp      \
    FacecopeCore/FFaceDetector.cpp      \
    FacecopeCore/FFaceRecognizer.cpp    \
    FacecopeCore/Settings.cpp           \
    FacecopeCore/FDatabaseDriver.cpp    \
    models/FMainFacecopeModel.cpp

HEADERS+=\
    widgets/include/FMainWindow.h           \
    widgets/include/FWorkingWidget.h        \
    widgets/include/FHelpWidget.h           \
    widgets/include/FSettingsWidget.h       \
    widgets/include/FImageShowDialog.h      \
    widgets/include/FImageDrawAreaWidget.h  \
    widgets/include/FSetFaceInfoDialog.h    \
    models/include/FFaceModel.h             \
    models/include/FImageProxyModel.h       \
    FacecopeCore/include/FImage.h           \
    FacecopeCore/include/FFace.h            \
    FacecopeCore/include/FacecopeTypes.h    \
    FacecopeCore/include/FacecopeUtils.h    \
    FacecopeCore/include/FFaceDetector.h    \
    FacecopeCore/include/FFaceRecognizer.h  \
    FacecopeCore/include/Settingsh          \
    FacecopeCore/include/FDatabaseDriver.h  \
    models/include/FMainFacecopeModel.h

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
