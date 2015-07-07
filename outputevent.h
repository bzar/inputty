#ifndef OUTPUTEVENT_H
#define OUTPUTEVENT_H

#include <QObject>
#include "quinput.h"

class OutputEvent : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int code READ getCode WRITE setCode NOTIFY codeChanged)
public:
  explicit OutputEvent(QObject *parent = 0);
  virtual ~OutputEvent();
  virtual QUinput::EventType getType() const;

  int getCode() const;
  void setCode(int code);
signals:
  void codeChanged(int code);
  void event(int type, int code, int value);
private:
  int _code = 0;
};

class KeyOutputEvent : public OutputEvent
{
  Q_OBJECT
  Q_PROPERTY(bool pressed READ getPressed WRITE setPressed NOTIFY pressedChanged)
public:
  QUinput::EventType getType() const;
  bool getPressed() const;
  void setPressed(bool pressed);
signals:
  void pressedChanged(bool pressed);
private:
  bool _pressed = false;
};
class AnyKeyOutputEvent : public OutputEvent
{
  Q_OBJECT
public:
  QUinput::EventType getType() const;
public slots:
  void event(int code, bool value);
};

class RelOutputEvent : public OutputEvent
{
  Q_OBJECT
  Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
public:
  QUinput::EventType getType() const;
  int getValue() const;
  void setValue(int value);
signals:
  void valueChanged(int value);
private:
  int _value = 0;
};
class AbsOutputEvent : public OutputEvent
{
  Q_OBJECT
  Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
public:
  QUinput::EventType getType() const;
  int getValue() const;
  void setValue(int value);
signals:
  void valueChanged(int value);
private:
  int _value = 0;
};
#endif // OUTPUTEVENT_H
