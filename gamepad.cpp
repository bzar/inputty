#include "gamepad.h"
#include <linux/input.h>
#include <QDebug>

Gamepad::Gamepad(QObject *parent) :
  QObject(parent), evdev()
{
  connect(&evdev, SIGNAL(absEvent(int,int)), this, SLOT(onAbsEvent(int,int)));
  connect(&evdev, SIGNAL(relEvent(int,int)), this, SLOT(onRelEvent(int,int)));
  connect(&evdev, SIGNAL(keyEvent(int,int)), this, SLOT(onKeyEvent(int,int)));
}

QString Gamepad::getPath() const
{
  return evdev.getPath();
}

void Gamepad::setPath(QString path)
{
  evdev.setPath(path);
}

void Gamepad::onRelEvent(int code, int value)
{

}

void Gamepad::onAbsEvent(int code, int value)
{
  switch(code)
  {
    case ABS_X: emit leftAnalogX(value); break;
    case ABS_Y: emit leftAnalogY(value); break;
    case ABS_RX: emit rightAnalogX(value); break;
    case ABS_RY: emit rightAnalogY(value); break;
    default: break;
  }
}

void Gamepad::onKeyEvent(int code, int value)
{
  switch(code)
  {
    case BTN_A: emit a(value); break;
    case BTN_B: emit b(value); break;
    case BTN_X: emit x(value); break;
    case BTN_Y: emit y(value); break;
    case BTN_START: emit start(value); break;
    case BTN_SELECT: emit select(value); break;
    case BTN_TL: emit l1(value); break;
    case BTN_TR: emit r1(value); break;
    case BTN_TL2: emit l2(value); break;
    case BTN_TR2: emit r2(value); break;
    case BTN_THUMBL: emit leftAnalogClick(value); break;
    case BTN_THUMBR: emit rightAnalogClick(value); break;
    case BTN_DPAD_UP: emit up(value); break;
    case BTN_DPAD_DOWN: emit down(value); break;
    case BTN_DPAD_LEFT: emit left(value); break;
    case BTN_DPAD_RIGHT: emit right(value); break;
    default: break;
  }
}
