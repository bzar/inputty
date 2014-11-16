#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QObject>
#include "qevdev.h"
#include "inputevent.h"
#include <QQmlListProperty>

class InputDevice : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<InputEvent> inputs READ inputs)
  Q_PROPERTY(QString path READ getPath WRITE setPath)
  Q_PROPERTY(bool debug READ getDebug WRITE setDebug)
  Q_CLASSINFO("DefaultProperty", "inputs")
public:
  explicit InputDevice(QObject *parent = 0);
  QQmlListProperty<InputEvent> inputs();

  QString getPath() const;
  void setPath(QString path);

  bool getDebug() const;
  void setDebug(bool debug);

signals:

public slots:

private slots:
  void handleEvent(quint16 type, quint16 code, qint32 value);

private:
  QEvdev _evdev;
  QList<InputEvent*> _inputs;
  bool _debug;
};

#endif // INPUTDEVICE_H