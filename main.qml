import QtQuick 2.3
import QtQuick.Controls 1.2
import EvdevDeviceListModel 1.0
import IODevices 1.0
import "inputcodes.js" as Codes

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Choose input")

    InputDevice {
      id: gamepad
      path: devices.currentItem.devicePath
      IKey {
        code: Codes.get("BTN_DPAD_UP")
        onPressedChanged: pandora_up.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_DPAD_DOWN")
        onPressedChanged: pandora_down.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_DPAD_LEFT")
        onPressedChanged: pandora_left.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_DPAD_RIGHT")
        onPressedChanged: pandora_right.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_A")
        onPressedChanged: pandora_x.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_B")
        onPressedChanged: pandora_b.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_X")
        onPressedChanged: pandora_y.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_Y")
        onPressedChanged: pandora_a.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_TL")
        onPressedChanged: pandora_l.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_TR")
        onPressedChanged: pandora_r.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_TL2")
        onPressedChanged: pandora_l2.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_TR2")
        onPressedChanged: pandora_r2.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_START")
        onPressedChanged: pandora_start.pressed = pressed
      }
      IKey {
        code: Codes.get("BTN_SELECT")
        onPressedChanged: pandora_select.pressed = pressed
      }
      IAbs {
        code: Codes.get("ABS_X")
        onValueChanged: nub0_x.value = value
      }
      IAbs {
        code: Codes.get("ABS_Y")
        onValueChanged: nub0_y.value = value
      }
      IAbs {
        code: Codes.get("ABS_RX")
        onValueChanged: nub1_x.value = value
      }
      IAbs {
        code: Codes.get("ABS_RY")
        onValueChanged: nub1_y.value = value
      }
    }

    OutputDevice {
      id: nub0
      name: "nub0"
      vendor: 1
      product: 1
      version: 1

      OAbs {
        id: nub0_x
        code: Codes.get("ABS_X")
      }
      OAbs {
        id: nub0_y
        code: Codes.get("ABS_Y")
      }
      Component.onCompleted: recreateDevice()
    }

    OutputDevice {
      id: nub1
      name: "nub1"
      vendor: 1
      product: 1
      version: 1

      OAbs {
        id: nub1_x
        code: Codes.get("ABS_X")
      }
      OAbs {
        id: nub1_y
        code: Codes.get("ABS_Y")
      }
      Component.onCompleted: recreateDevice()
    }
    OutputDevice {
      id: pandora
      name: "gpio-keys"
      vendor: 1
      product: 1
      version: 1

      OKey {
        id: pandora_up
        code: Codes.get("KEY_UP")
      }
      OKey {
        id: pandora_down
        code: Codes.get("KEY_DOWN")
      }
      OKey {
        id: pandora_left
        code: Codes.get("KEY_LEFT")
      }
      OKey {
        id: pandora_right
        code: Codes.get("KEY_RIGHT")
      }
      OKey {
        id: pandora_a
        code: Codes.get("KEY_HOME")
      }
      OKey {
        id: pandora_b
        code: Codes.get("KEY_END")
      }
      OKey {
        id: pandora_x
        code: Codes.get("KEY_PAGEDOWN")
      }
      OKey {
        id: pandora_y
        code: Codes.get("KEY_PAGEUP")
      }
      OKey {
        id: pandora_l
        code: Codes.get("KEY_RIGHTSHIFT")
      }
      OKey {
        id: pandora_r
        code: Codes.get("KEY_RIGHTCTRL")
      }
      OKey {
        id: pandora_l2
        code: Codes.get("KEY_KPPLUS")
      }
      OKey {
        id: pandora_r2
        code: Codes.get("KEY_KPMINUS")
      }
      OKey {
        id: pandora_start
        code: Codes.get("KEY_LEFTALT")
      }
      OKey {
        id: pandora_select
        code: Codes.get("KEY_LEFTCTRL")
      }
      OKey {
        id: pandora_pandora
        code: Codes.get("KEY_MENU")
      }
      OKey {
        id: pandora_hold
        code: Codes.get("KEY_COFFEE")
      }

      Component.onCompleted: recreateDevice()
    }

    ListView {
      id: devices
      anchors.fill: parent

      model: EvdevDeviceListModel {

      }

      highlight: Rectangle {
        width: devices.width
        height: 20
        color: "lightsteelblue"
      }

      highlightFollowsCurrentItem: true

      delegate: Item {
        property string devicePath: path
        width: devices.width
        height: 20
        MouseArea {
          anchors.fill: parent
          onClicked: devices.currentIndex = index
        }
        Row {
          id: deviceInfo
          spacing: 16
          Text {
            text: name
          }
          Text {
            text: devicePath
          }
        }
      }
    }
}
