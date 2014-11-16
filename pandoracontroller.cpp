#include "pandoracontroller.h"
#include "assert.h"
#include <QDebug>

PandoraController::PandoraController(QObject *parent) :
  QObject(parent), buttons(), nubl(), nubr()
{
  assert(buttons.open("/dev/uinput", QUinput::I2C, "gpio-keys", 1, 1, 1)
         && nubl.open("/dev/uinput", QUinput::I2C, "nub0", 1, 1, 1)
         && nubr.open("/dev/uinput", QUinput::I2C, "nub1", 1, 1, 1)
         && "Error opening devices");

  assert(buttons.add(QUinput::KEY) && "Error adding KEY event type");
  assert(buttons.add(QUinput::KEY, BTN_X)
         && buttons.add(QUinput::KEY, KEY_PAGEUP)
         && buttons.add(QUinput::KEY, KEY_PAGEDOWN)
         && buttons.add(QUinput::KEY, KEY_HOME)
         && buttons.add(QUinput::KEY, KEY_END)
         && buttons.add(QUinput::KEY, BTN_TR)
         && buttons.add(QUinput::KEY, BTN_START)
         && buttons.add(QUinput::KEY, BTN_SELECT)
         && buttons.add(QUinput::KEY, BTN_MODE)
         && buttons.add(QUinput::KEY, KEY_UP)
         && buttons.add(QUinput::KEY, KEY_DOWN)
         && buttons.add(QUinput::KEY, KEY_LEFT)
         && buttons.add(QUinput::KEY, KEY_RIGHT)
         && "Error adding buttons");

  assert(nubl.add(QUinput::ABS) && "Error adding ABS event type");
  assert(nubl.add(QUinput::ABS, ABS_X) && nubl.add(QUinput::ABS, ABS_Y) && "Error adding left nub");

  assert(nubr.add(QUinput::ABS) && "Error adding ABS event type");
  assert(nubr.add(QUinput::ABS, ABS_X) && nubr.add(QUinput::ABS, ABS_Y) && "Error adding right nub");

  assert(buttons.create()
         && nubl.create()
         && nubr.create()
         && "Error creating devices");
}

void PandoraController::left(bool v)
{
  buttons.event(QUinput::KEY, KEY_LEFT, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::right(bool v)
{
  buttons.event(QUinput::KEY, KEY_RIGHT, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::up(bool v)
{
  buttons.event(QUinput::KEY, KEY_UP, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::down(bool v)
{
  buttons.event(QUinput::KEY, KEY_DOWN, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::a(bool v)
{
  buttons.event(QUinput::KEY, KEY_HOME, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::b(bool v)
{
  buttons.event(QUinput::KEY, KEY_END, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::x(bool v)
{
  buttons.event(QUinput::KEY, KEY_PAGEDOWN, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::y(bool v)
{
  buttons.event(QUinput::KEY, KEY_PAGEUP, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::l(bool v)
{
  buttons.event(QUinput::KEY, BTN_TL, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::r(bool v)
{
  buttons.event(QUinput::KEY, BTN_TR, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::pandora(bool v)
{
  buttons.event(QUinput::KEY, BTN_MODE, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::select(bool v)
{
  buttons.event(QUinput::KEY, BTN_SELECT, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::start(bool v)
{
  buttons.event(QUinput::KEY, BTN_START, v ? 1 : 0);
  buttons.sync();
}

void PandoraController::nublx(int v)
{
  nubl.event(QUinput::ABS, ABS_X, v);
  nubl.sync();
}

void PandoraController::nubly(int v)
{
  nubl.event(QUinput::ABS, ABS_Y,  v);
  nubl.sync();
}

void PandoraController::nubrx(int v)
{
  nubr.event(QUinput::ABS, ABS_X,  v);
  nubr.sync();
}

void PandoraController::nubry(int v)
{
  nubr.event(QUinput::ABS, ABS_Y, v);
  nubr.sync();
}
