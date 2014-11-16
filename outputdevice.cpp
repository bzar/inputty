#include "outputdevice.h"
#include <QSet>
#include <QDebug>

namespace
{
}

OutputDevice::OutputDevice(QObject *parent) :
  QObject(parent), _uinput(), _name(), _product(0), _vendor(0), _version(0), _outputs(), _debug(false)
{
}

QQmlListProperty<OutputEvent> OutputDevice::outputs()
{
  return QQmlListProperty<OutputEvent>(this, &_outputs, outputAppend, outputCount, outputAt, outputClear);
}

QString OutputDevice::getName() const
{
  return _name;
}

void OutputDevice::setName(QString name)
{
  if(name != _name)
  {
    _name = name;
    emit nameChanged(_name);
  }
}

int OutputDevice::getProduct() const
{
  return _product;
}

void OutputDevice::setProduct(int product)
{
  if(product != _product)
  {
    _product = product;
    emit productChanged(_product);
  }
}

int OutputDevice::getVendor() const
{
  return _vendor;
}

void OutputDevice::setVendor(int vendor)
{
  if(vendor != _vendor)
  {
    _vendor = vendor;
    emit vendorChanged(_vendor);
  }
}

int OutputDevice::getVersion() const
{
  return _version;
}

void OutputDevice::setVersion(int version)
{
  if(version != _version)
  {
    _version = version;
    emit versionChanged(_version);
  }
}

bool OutputDevice::getDebug() const
{
  return _debug;
}

void OutputDevice::setDebug(bool debug)
{
  _debug = debug;
}

void OutputDevice::handleEvent(int type, int code, int value)
{
  if(_uinput.getStatus() != QUinput::READY)
    recreateDevice();

  if(_debug) qDebug() << _name << "sending event" << type << code << value;
  _uinput.event(static_cast<QUinput::EventType>(type), code, value);
  _uinput.sync();

}
void OutputDevice::recreateDevice()
{
  if(_debug) qDebug() << _name << "creating device";
  _uinput.destroy();
  _uinput.open("/dev/uinput", QUinput::USB, _name, _product, _vendor, _version);

  QSet<QUinput::EventType> addedTypes;
  foreach (OutputEvent const* output, _outputs) {
    QUinput::EventType type = output->getType();
    if(!addedTypes.contains(type))
    {
      _uinput.add(type);
    }
    _uinput.add(type, output->getCode());
  }
  _uinput.create();
}

void OutputDevice::outputAppend(QQmlListProperty<OutputEvent>* prop, OutputEvent* output)
{
  static_cast<QList<OutputEvent*>*>(prop->data)->append(output);
  OutputDevice* device = qobject_cast<OutputDevice*>(prop->object);
  connect(output, SIGNAL(event(int,int,int)), device, SLOT(handleEvent(int,int,int)));
}
OutputEvent* OutputDevice::outputAt(QQmlListProperty<OutputEvent>* prop, int index)
{
  return static_cast<QList<OutputEvent*>*>(prop->data)->at(index);
}
void OutputDevice::outputClear(QQmlListProperty<OutputEvent>* prop)
{
  OutputDevice* device = qobject_cast<OutputDevice*>(prop->object);
  foreach (OutputEvent const* output, device->_outputs) {
    disconnect(output, 0, device, 0);
  }
  static_cast<QList<OutputEvent*>*>(prop->data)->clear();
  device->recreateDevice();
}
int OutputDevice::outputCount(QQmlListProperty<OutputEvent>* prop)
{
  return static_cast<QList<OutputEvent*>*>(prop->data)->count();
}
