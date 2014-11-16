#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QQuickItem>

#include "evdevdevicelistmodel.h"
#include "inputdevice.h"
#include "outputdevice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // @uri fi.bzar.qmlcomponents
    qmlRegisterType<EvdevDeviceListModel>("EvdevDeviceListModel", 1, 0, "EvdevDeviceListModel");

    qmlRegisterType<InputDevice>("IODevices", 1, 0, "InputDevice");

    qmlRegisterType<InputEvent>();
    qmlRegisterType<KeyInputEvent>("IODevices", 1, 0, "IKey");
    qmlRegisterType<RelInputEvent>("IODevices", 1, 0, "IRel");
    qmlRegisterType<AbsInputEvent>("IODevices", 1, 0, "IAbs");

    qmlRegisterType<OutputDevice>("IODevices", 1, 0, "OutputDevice");
    qmlRegisterType<OutputEvent>();
    qmlRegisterType<KeyOutputEvent>("IODevices", 1, 0, "OKey");
    qmlRegisterType<RelOutputEvent>("IODevices", 1, 0, "ORel");
    qmlRegisterType<AbsOutputEvent>("IODevices", 1, 0, "OAbs");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
    return EXIT_SUCCESS;
}
