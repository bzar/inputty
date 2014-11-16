TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    quinput.cpp \
    pandoracontroller.cpp \
    qevdev.cpp \
    gamepad.cpp \
    evdevdevicelistmodel.cpp \
    inputdevice.cpp \
    inputevent.cpp \
    outputdevice.cpp \
    outputevent.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    quinput.h \
    pandoracontroller.h \
    qevdev.h \
    gamepad.h \
    evdevdevicelistmodel.h \
    inputdevice.h \
    inputevent.h \
    outputdevice.h \
    outputevent.h
