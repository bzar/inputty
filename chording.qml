import QtQuick 2.0
import EvdevDeviceListModel 1.0
import IODevices 1.0
import "qrc:/inputcodes.js" as Codes

Item {
  InputDevice {
    path: devices.path
    grab: true
    IAnyKey {
      property int previousDown: 0
      onEvent: {
        if(value && (code === Codes.get("KEY_J") || code === Codes.get("KEY_K"))) {
          if(previousDown && previousDown !== code) {
            out.event(Codes.get("KEY_ESC"), true);
            out.event(Codes.get("KEY_ESC"), false);
            previousDown = 0;
          } else {
            previousDown = code;
          }
        } else if(previousDown) {
          out.event(previousDown, true);
          out.event(code, value);
          previousDown = 0;
        } else {
          out.event(code, value);
        }
      }
    }
  }
  OutputDevice {
    name: "Fakeboard"
    product: 1
    vendor: 1
    version: 1
    codes: Codes.keys()

    OAnyKey {
      id: out
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

