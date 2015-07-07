#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QQuickItem>

#include "evdevdevicelistmodel.h"
#include "inputdevice.h"
#include "outputdevice.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(argc < 2)
    {
      std::cout << "Usage: " << argv[0] << "<inputty qml file>" << std::endl;
      return 1;
    }

    // @uri fi.bzar.qmlcomponents
    qmlRegisterType<EvdevDeviceListModel>("EvdevDeviceListModel", 1, 0, "EvdevDeviceListModel");

    qmlRegisterType<InputDevice>("IODevices", 1, 0, "InputDevice");

    qmlRegisterType<InputEvent>();
    qmlRegisterType<KeyInputEvent>("IODevices", 1, 0, "IKey");
    qmlRegisterType<AnyKeyInputEvent>("IODevices", 1, 0, "IAnyKey");
    qmlRegisterType<RelInputEvent>("IODevices", 1, 0, "IRel");
    qmlRegisterType<AbsInputEvent>("IODevices", 1, 0, "IAbs");

    qmlRegisterType<OutputDevice>("IODevices", 1, 0, "OutputDevice");
    qmlRegisterType<OutputEvent>();
    qmlRegisterType<KeyOutputEvent>("IODevices", 1, 0, "OKey");
    qmlRegisterType<AnyKeyOutputEvent>("IODevices", 1, 0, "OAnyKey");
    qmlRegisterType<RelOutputEvent>("IODevices", 1, 0, "ORel");
    qmlRegisterType<AbsOutputEvent>("IODevices", 1, 0, "OAbs");
    QQmlApplicationEngine engine;
    engine.load(QUrl(argv[1]));


    return app.exec();
    return EXIT_SUCCESS;
}
