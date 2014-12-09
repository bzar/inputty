import QtQuick 2.0
import QtQuick.Controls 1.2
import EvdevDeviceListModel 1.0
import IODevices 1.0
import "qrc:/inputcodes.js" as Codes
import "qrc:/collections.js" as C

ApplicationWindow {
  visible: true
  width: 400
  height: 400
  title: qsTr("Wiimotes")

  property var mappings: [
    {
      "up": "KEY_UP", "down": "KEY_DOWN", "left": "KEY_LEFT", "right": "KEY_RIGHT",
      "a": "KEY_A", "b": "KEY_B", "1": "KEY_1", "2": "KEY_2",
      "+": "KEY_KPPLUS", "-": "KEY_KPMINUS", "home": "KEY_ENTER"
    },
    {
      "up": "KEY_E", "down": "KEY_D", "left": "KEY_S", "right": "KEY_F",
      "a": "KEY_W", "b": "KEY_R", "1": "KEY_3", "2": "KEY_4",
      "+": "KEY_T", "-": "KEY_G", "home": "KEY_Q"
    },
    {
      "up": "KEY_U", "down": "KEY_J", "left": "KEY_H", "right": "KEY_K",
      "a": "KEY_Y", "b": "KEY_I", "1": "KEY_5", "2": "KEY_6",
      "+": "KEY_O", "-": "KEY_L", "home": "KEY_P"
    },
    {
      "up": "KEY_KP8", "down": "KEY_KP2", "left": "KEY_KP4", "right": "KEY_KP6",
      "a": "KEY_KP7", "b": "KEY_KP9", "1": "KEY_KP1", "2": "KEY_KP3",
      "+": "KEY_KP0", "-": "KEY_KPDOT", "home": "KEY_KP5"
    }
  ]

  Component {
    id: wiimoteComponent

    Item {
      property alias path: input.path
      property var mapping

      OutputDevice {
        name: "Wiimote"
        product: 1
        vendor: 1
        version: 1

        OKey {
          code: Codes.get(mapping["up"])
          pressed: up.pressed
        }
        OKey {
          code: Codes.get(mapping["down"])
          pressed: down.pressed
        }
        OKey {
          code: Codes.get(mapping["left"])
          pressed: left.pressed
        }
        OKey {
          code: Codes.get(mapping["right"])
          pressed: right.pressed
        }
        OKey {
          code: Codes.get(mapping["a"])
          pressed: a.pressed
        }
        OKey {
          code: Codes.get(mapping["b"])
          pressed: b.pressed
        }
        OKey {
          code: Codes.get(mapping["1"])
          pressed: one.pressed
        }
        OKey {
          code: Codes.get(mapping["2"])
          pressed: two.pressed
        }
        OKey {
          code: Codes.get(mapping["+"])
          pressed: plus.pressed
        }
        OKey {
          code: Codes.get(mapping["-"])
          pressed: minus.pressed
        }
        OKey {
          code: Codes.get(mapping["home"])
          pressed: home.pressed
        }
      }

      InputDevice {
        id: input
        IKey {
          id: up
          code: Codes.get("KEY_UP")
        }
        IKey {
          id: down
          code: Codes.get("KEY_DOWN")
        }
        IKey {
          id: left
          code: Codes.get("KEY_LEFT")
        }
        IKey {
          id: right
          code: Codes.get("KEY_RIGHT")
        }
        IKey {
          id: a
          code: Codes.get("BTN_A")
        }
        IKey {
          id: b
          code: Codes.get("BTN_B")
        }
        IKey {
          id: one
          code: Codes.get("BTN_1")
        }
        IKey {
          id: two
          code: Codes.get("BTN_2")
        }
        IKey {
          id: plus
          code: Codes.get("KEY_NEXT")
        }
        IKey {
          id: minus
          code: Codes.get("KEY_PREVIOUS")
        }
        IKey {
          id: home
          code: Codes.get("KEY_MODE")
        }
      }
    }
  }

  EvdevDeviceListModel {
    id: devices
    property variant wiimotes: findWiimotes()

    function findWiimotes() {
      var result = []
      for(var i = 0; i < devices.length; ++i) {
        var device = devices.get(i);
        if("Nintendo Wii Remote" === device.name) {
          result.push(device.path);
        }
      }
      return result;
    }
  }

  Item {
    id: container
    function clear() {
      for(var i = 0; i < children.length; ++i) {
        children[i].destroy();
      }
    }
  }

  function refresh() {
    var wiimotes = devices.wiimotes;
    var removed = C.filter(container.children, function(c) { return !C.contains(wiimotes, c.path); });
    var existing = C.map(container.children, function(c) { return c.path; });
    var created = C.filter(wiimotes, function(p) { return !C.contains(existing, p); });

    if(created.length > 0 || removed.length > 0) {
      container.clear();
      for(var i = 0; i < wiimotes.length; ++i) {
        wiimoteComponent.createObject(container, { "path": wiimotes[i], "mapping": mappings[i]});
      }
    }
  }

  Connections {
    target: devices
    onWiimotesChanged: refresh()
  }

  Component.onCompleted: refresh()

  Row {
    id: wiimoteImages
    anchors.fill: parent
    Repeater {
      model: container.children.length
      delegate: Image {
        source: "img/WiiRemote_by_nevralgic.png"
        fillMode: Image.PreserveAspectFit
        height: wiimoteImages.height
      }
    }
  }
}
