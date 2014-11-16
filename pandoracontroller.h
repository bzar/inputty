#ifndef PANDORACONTROLLER_H
#define PANDORACONTROLLER_H

#include <QObject>
#include "quinput.h"

class PandoraController : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(PandoraController)

public:
  explicit PandoraController(QObject *parent = 0);

signals:

public slots:
  void left(bool);
  void right(bool);
  void up(bool);
  void down(bool);
  void a(bool);
  void b(bool);
  void x(bool);
  void y(bool);
  void l(bool);
  void r(bool);
  void pandora(bool);
  void select(bool);
  void start(bool);
  void nublx(int);
  void nubly(int);
  void nubrx(int);
  void nubry(int);

private:
  QUinput buttons;
  QUinput nubl;
  QUinput nubr;

};

#endif // PANDORACONTROLLER_H
