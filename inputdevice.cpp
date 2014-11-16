#include "inputdevice.h"
#include <QDebug>

namespace
{
  void inputAppend(QQmlListProperty<InputEvent>* prop, InputEvent* input)
  {
    static_cast<QList<InputEvent*>*>(prop->data)->append(input);
  }
  InputEvent* inputAt(QQmlListProperty<InputEvent>* prop, int index)
  {
    return static_cast<QList<InputEvent*>*>(prop->data)->at(index);
  }
  void inputClear(QQmlListProperty<InputEvent>* prop)
  {
    static_cast<QList<InputEvent*>*>(prop->data)->clear();
  }
  int inputCount(QQmlListProperty<InputEvent>* prop)
  {
    return static_cast<QList<InputEvent*>*>(prop->data)->count();
  }
}
InputDevice::InputDevice(QObject *parent) :
  QObject(parent), _evdev(), _inputs(), _debug(false)
{
  connect(&_evdev, SIGNAL(rawEvent(quint16,quint16,qint32)), this, SLOT(handleEvent(quint16,quint16,qint32)));
}

QQmlListProperty<InputEvent> InputDevice::inputs()
{
  return QQmlListProperty<InputEvent>(this, &_inputs, inputAppend, inputCount, inputAt, inputClear);
}

QString InputDevice::getPath() const
{
  return _evdev.getPath();
}

void InputDevice::setPath(QString path)
{
  _evdev.setPath(path);
}

void InputDevice::handleEvent(quint16 type, quint16 code, qint32 value)
{
  if(_debug) qDebug() << _evdev.getPath() << "receiving event" << type << code << value;
  foreach(InputEvent* input, _inputs)
  {
    input->handleEvent(type, code, value);
  }
}

bool InputDevice::getDebug() const
{
  return _debug;
}

void InputDevice::setDebug(bool debug)
{
  _debug = debug;
}
