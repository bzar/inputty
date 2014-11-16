#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <QObject>
#include "qevdev.h"

class InputEvent : public QObject
{
  Q_OBJECT
public:
  InputEvent(QObject* parent = 0);
  virtual ~InputEvent();
  virtual void handleEvent(int type, int code, int value);
};

class KeyInputEvent : public InputEvent
{
  Q_OBJECT
  Q_PROPERTY(int code READ getCode WRITE setCode)
  Q_PROPERTY(bool pressed READ getPressed NOTIFY pressedChanged)
public:
  void handleEvent(int type, int code, int value);
  int getCode() const;
  void setCode(int code);

  bool getPressed() const;

signals:
  void pressedChanged(bool pressed);
private:
  void setPressed(bool value);
  int _code;
  bool _pressed;
};
class RelInputEvent : public InputEvent
{
  Q_OBJECT
  Q_PROPERTY(int code READ getCode WRITE setCode)
public:
  void handleEvent(int type, int code, int value);
  int getCode() const;
  void setCode(int code);

signals:
  void valueChanged(int value);
private:
  int _code;
};
class AbsInputEvent : public InputEvent
{
  Q_OBJECT
  Q_PROPERTY(int code READ getCode WRITE setCode)
  Q_PROPERTY(int value READ getValue NOTIFY valueChanged)
public:
  void handleEvent(int type, int code, int value);
  int getCode() const;
  void setCode(int code);

  int getValue() const;

signals:
  void valueChanged(int value);
private:
  void setValue(int value);
  int _code;
  int _value;
};
#endif // INPUTEVENT_H
