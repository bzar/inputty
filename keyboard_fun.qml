import QtQuick 2.0
import EvdevDeviceListModel 1.0
import IODevices 1.0
import "qrc:/inputcodes.js" as Codes

Item {
  InputDevice {
    path: devices.path
    IKey {
      id: keyf
      code: Codes.get("KEY_F")
    }
  }
  OutputDevice {
    name: "Fakeboard"
    product: 1
    vendor: 1
    version: 1

    OKey {
      code: Codes.get("KEY_X")
      pressed: keyf.pressed
    }
  }
  EvdevDeviceListModel {
    id: devices
    property string path: getPath()
    function getPath() {
      for(var i = 0; i < devices.length; ++i) {
        var device = devices.get(i);
        console.log("Device " + device.name + " at " + device.path);
        if(/.*keyboard.*/.test(device.name)) {
          console.log("^ selected");
          return device.path;
        }
      }
      return "";
    }
  }
}
