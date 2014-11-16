#ifndef QUINPUT_H
#define QUINPUT_H

#include <QObject>
#include <linux/input.h>

class QUinput : public QObject
{
  Q_OBJECT
public:
  enum Bus {
    PCI	=	BUS_PCI,
    ISAPNP = BUS_ISAPNP,
    USB = BUS_USB,
    HIL = BUS_HIL,
    BLUETOOTH = BUS_BLUETOOTH,
    VIRTUAL = BUS_VIRTUAL,
    ISA = BUS_ISA,
    I8042 = BUS_I8042,
    XTKBD = BUS_XTKBD,
    RS232 =BUS_RS232,
    GAMEPORT = BUS_GAMEPORT,
    PARPORT = BUS_PARPORT,
    AMIGAA = BUS_AMIGA,
    ADB = BUS_ADB,
    I2C = BUS_I2C,
    HOST = BUS_HOST,
    GSC = BUS_GSC,
    ATARI = BUS_ATARI,
    SPI = BUS_SPI
  };

  enum EventType {
    KEY = EV_KEY,
    REL = EV_REL,
    ABS = EV_ABS
  };

  enum Status {
    CLOSED, OPEN, READY
  };

  explicit QUinput(QObject *parent = 0);
  ~QUinput();

  bool open(QString path, Bus bus, QString name, quint16 product, quint16 vendor, quint16 version);
  bool add(EventType type);
  bool add(EventType type, quint16 code);
  bool create();
  bool destroy();

  Status getStatus() const;

signals:
  void statusChanged(Status);

public slots:
  bool event(EventType type, quint16 code, qint32 value);
  bool sync();

private:
  bool send(quint16 type, quint16 code, qint32 value);
  int eventTypeToSetEventType(EventType type) const;
  int fd;
  Status status;
};

#endif // QUINPUT_H
