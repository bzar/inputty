#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QObject>
#include "qevdev.h"

class Gamepad : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ getPath WRITE setPath)
public:
  explicit Gamepad(QObject *parent = 0);

signals:
  void left(bool pressed);
  void right(bool pressed);
  void up(bool pressed);
  void down(bool pressed);
  void a(bool pressed);
  void b(bool pressed);
  void x(bool pressed);
  void y(bool pressed);
  void l1(bool pressed);
  void r1(bool pressed);
  void l2(bool pressed);
  void r2(bool pressed);
  void select(bool pressed);
  void start(bool pressed);
  void leftAnalogClick(bool pressed);
  void rightAnalogClick(bool pressed);
  void leftAnalogX(float value);
  void leftAnalogY(float value);
  void rightAnalogX(float value);
  void rightAnalogY(float value);

public slots:
  QString getPath() const;
  void setPath(QString path);

private slots:
  void onRelEvent(int code, int value);
  void onAbsEvent(int code, int value);
  void onKeyEvent(int code, int value);
private:
  QEvdev evdev;
};

#endif // GAMEPAD_H
