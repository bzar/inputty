#include "qevdev.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <QDebug>

QEvdev::QEvdev(QObject* parent) :
  QObject(parent), listener(0)
{

}

QEvdev::QEvdev(QString path, QObject *parent) :
  QObject(parent), listener(0)
{
  setPath(path);
}

QEvdev::~QEvdev()
{
  if(listener)
  {
    listener->stop();
    listener->wait();
    delete listener;
  }
}

void QEvdev::setPath(QString path)
{
  if(path != this->path)
  {
    this->path = path;
    if(listener)
    {
      listener->stop();
      listener->wait();
      delete listener;
    }
    listener = new qevdev::Listener(path);
    connect(listener, SIGNAL(evdevEvent(quint16,quint16,qint32)), this, SLOT(onListenerEvent(quint16,quint16,qint32)), Qt::QueuedConnection);
    connect(listener, SIGNAL(evdevEvent(quint16,quint16,qint32)), this, SIGNAL(rawEvent(quint16,quint16,qint32)));
    listener->start();
  }
}

QString QEvdev::getPath() const
{
  return path;
}

void QEvdev::onListenerEvent(quint16 type, quint16 code, qint32 value)
{
  switch(type)
  {
    case EV_ABS:
      emit absEvent(code, value);
      break;
    case EV_REL:
      emit relEvent(code, value);
      break;
    case EV_KEY:
      emit keyEvent(code, value);
      break;
    default:
      break;
  }
}


qevdev::Listener::Listener(QString path, QObject* parent) : QThread(parent), fd(-1), shouldStop(false)
{
  fd = open(path.toLocal8Bit(), O_RDONLY | O_NDELAY);
}

qevdev::Listener::~Listener()
{
  if(fd >= 0)
    close(fd);
}

void qevdev::Listener::run()
{
  shouldStop = false;
  while(!shouldStop)
  {
    // Wait for input while checking stop condition every 100ms
    fd_set fds;
    timeval timeout = {0, 100000};
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    if(select(FD_SETSIZE, &fds, NULL, NULL, &timeout ) <= 0)
      continue;

    // Got input - read events and emit signals
    input_event events[64];
    int numBytes = read (fd, events, sizeof(input_event) * 64);
    int numEvents = numBytes / sizeof(input_event);

    for(int i = 0; i < numEvents; ++i)
    {
      input_event const& e = events[i];

      // Skip uninteresting events
      if(e.type != EV_ABS && e.type != EV_REL && e.type != EV_KEY)
        continue;

      emit evdevEvent( e.type, e.code, e.value);
    }
  }
}

void qevdev::Listener::stop()
{
  shouldStop = true;
}
