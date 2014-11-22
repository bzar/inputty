#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <QObject>
#include "quinput.h"
#include "outputevent.h"
#include <QQmlListProperty>
#include <QTimer>

class OutputDevice : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(OutputDevice)
  Q_PROPERTY(QQmlListProperty<OutputEvent> outputs READ outputs)
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(int product READ getProduct WRITE setProduct NOTIFY productChanged)
  Q_PROPERTY(int vendor READ getVendor WRITE setVendor NOTIFY vendorChanged)
  Q_PROPERTY(int version READ getVersion WRITE setVersion NOTIFY versionChanged)
  Q_PROPERTY(bool debug READ getDebug WRITE setDebug)
  Q_CLASSINFO("DefaultProperty", "outputs")

public:
  explicit OutputDevice(QObject *parent = 0);
  QQmlListProperty<OutputEvent> outputs();

  QString getName() const;
  void setName(QString name);

  int getProduct() const;
  void setProduct(int product);

  int getVendor() const;
  void setVendor(int vendor);

  int getVersion() const;
  void setVersion(int version);

  bool getDebug() const;
  void setDebug(bool debug);

signals:
  void nameChanged(QString name);
  void productChanged(int value);
  void vendorChanged(int value);
  void versionChanged(int value);

public slots:
  void recreateDevice();

private slots:
  void handleEvent(int, int, int);

private:
  QUinput _uinput;
  QString _name;
  int _product;
  int _vendor;
  int _version;
  QList<OutputEvent*> _outputs;
  bool _debug;
  QTimer _graceTimer;

  static void outputAppend(QQmlListProperty<OutputEvent>* prop, OutputEvent* output);
  static OutputEvent* outputAt(QQmlListProperty<OutputEvent>* prop, int index);
  static void outputClear(QQmlListProperty<OutputEvent>* prop);
  static int outputCount(QQmlListProperty<OutputEvent>* prop);
};

#endif // OUTPUTDEVICE_H
