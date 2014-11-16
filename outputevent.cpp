#include "outputevent.h"

OutputEvent::OutputEvent(QObject *parent) :
  QObject(parent)
{
}

OutputEvent::~OutputEvent()
{

}

QUinput::EventType OutputEvent::getType() const
{
  return QUinput::KEY;
}

int OutputEvent::getCode() const
{
  return _code;
}

void OutputEvent::setCode(int code)
{
  if(code != _code)
  {
    _code = code;
    emit codeChanged(_code);
  }

}


QUinput::EventType KeyOutputEvent::getType() const
{
  return QUinput::KEY;
}

bool KeyOutputEvent::getPressed() const
{
  return _pressed;
}

void KeyOutputEvent::setPressed(bool pressed)
{
  if(pressed != _pressed)
  {
    _pressed = pressed;
    emit pressedChanged(_pressed);
  }
  emit event(getType(), getCode(), pressed ? 1 : 0);
}


QUinput::EventType RelOutputEvent::getType() const
{
  return QUinput::REL;
}

int RelOutputEvent::getValue() const
{
  return _value;
}

void RelOutputEvent::setValue(int value)
{
  if(value != _value)
  {
    _value = value;
    emit valueChanged(_value);
  }
  emit event(getType(), getCode(), _value);
}

QUinput::EventType AbsOutputEvent::getType() const
{
  return QUinput::ABS;
}

int AbsOutputEvent::getValue() const
{
  return _value;
}

void AbsOutputEvent::setValue(int value)
{
  if(value != _value)
  {
    _value = value;
    emit valueChanged(_value);
  }
  emit event(getType(), getCode(), _value);
}
