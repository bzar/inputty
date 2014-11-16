#include "inputevent.h"
#include <linux/input.h>
#include <QDebug>

InputEvent::InputEvent(QObject* parent) : QObject(parent)
{
}

InputEvent::~InputEvent()
{

}

void InputEvent::handleEvent(int type, int code, int value)
{
  Q_UNUSED(type)
  Q_UNUSED(code)
  Q_UNUSED(value)
}


void KeyInputEvent::handleEvent(int type, int code, int value)
{
  if(type == EV_KEY && code == _code)
  {
    setPressed(value);
  }
}

int KeyInputEvent::getCode() const
{
  return _code;
}

void KeyInputEvent::setCode(int code)
{
  _code = code;
}
bool KeyInputEvent::getPressed() const
{
  return _pressed;
}

void KeyInputEvent::setPressed(bool value)
{
  if(_pressed != value)
  {
    _pressed = value;
    emit pressedChanged(_pressed);
  }
}



void RelInputEvent::handleEvent(int type, int code, int value)
{
  if(type == EV_REL && code == _code)
  {
    emit valueChanged(value);
  }
}

int RelInputEvent::getCode() const
{
  return _code;
}

void RelInputEvent::setCode(int code)
{
  _code = code;
}


void AbsInputEvent::handleEvent(int type, int code, int value)
{
  if(type == EV_ABS && code == _code)
  {
    setValue(value);
  }
}

int AbsInputEvent::getCode() const
{
  return _code;
}

void AbsInputEvent::setCode(int code)
{
  _code = code;
}

int AbsInputEvent::getValue() const
{
  return _value;
}

void AbsInputEvent::setValue(int value)
{
  if(value != _value)
  {
    _value = value;
    emit valueChanged(_value);
  }
}
