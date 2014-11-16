#include "quinput.h"
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <assert.h>


QUinput::QUinput(QObject *parent) :
  QObject(parent), fd(0), status(CLOSED)
{
}

QUinput::~QUinput()
{
  destroy();
}

bool QUinput::open(QString path, QUinput::Bus bus, QString name, quint16 product, quint16 vendor, quint16 version)
{
  if(status != CLOSED)
    return false;

  fd = ::open(path.toLocal8Bit(), O_WRONLY | O_NONBLOCK);

  if(fd < 0)
    return false;

  uinput_user_dev device;
  memset(&device,0,sizeof(device));
  qstrncpy(device.name, name.toLocal8Bit(), UINPUT_MAX_NAME_SIZE);
  device.id.bustype = static_cast<quint16>(bus);
  device.id.product = static_cast<quint16>(product);
  device.id.vendor = static_cast<quint16>(vendor);
  device.id.version = static_cast<quint16>(version);

  if(write(fd, &device, sizeof(device)) != sizeof(device))
  {
    close(fd);
    return false;
  }

  status = OPEN;
  emit statusChanged(status);
  return true;
}

bool QUinput::add(QUinput::EventType type)
{
  if(status != OPEN)
    return false;

  return ioctl(fd, UI_SET_EVBIT, static_cast<quint16>(type)) >= 0;
}
bool QUinput::add(QUinput::EventType type, quint16 code)
{
  if(status != OPEN)
    return false;

  return ioctl(fd, eventTypeToSetEventType(type), code) >= 0;
}

bool QUinput::create()
{
  if(status != OPEN)
    return false;

  if(ioctl(fd, UI_DEV_CREATE) < 0)
    return false;

  status = READY;
  emit statusChanged(status);
  return true;
}

bool QUinput::destroy()
{
  if(status == CLOSED)
    return false;

  if(status == READY)
    ioctl(fd, UI_DEV_DESTROY);

  close(fd);
  fd = 0;
  status = CLOSED;
  emit statusChanged(status);

  return true;
}

QUinput::Status QUinput::getStatus() const
{
  return status;
}

bool QUinput::event(QUinput::EventType type, quint16 code, qint32 value)
{
  return send(static_cast<quint16>(type), code, value);
}

bool QUinput::sync()
{
  return send(EV_SYN, 0, 0);
}

bool QUinput::send(quint16 type, quint16 code, qint32 value)
{
  if(status != READY)
    return false;

  input_event event;
  memset(&event,0,sizeof(event));
  event.type = type;
  event.code = code;
  event.value = value;

  return write(fd, &event, sizeof(event)) == sizeof(event);
}

int QUinput::eventTypeToSetEventType(QUinput::EventType type) const
{
  switch(type)
  {
    case KEY: return UI_SET_KEYBIT;
    case REL: return UI_SET_RELBIT;
    case ABS: return UI_SET_ABSBIT;
    default: assert(0);
  }
}

