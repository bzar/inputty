#ifndef QEVDEV_H
#define QEVDEV_H

#include <QObject>
#include <QThread>

namespace qevdev
{
  class Listener : public QThread
  {
    Q_OBJECT
  public:
    explicit Listener(QString path, QObject *parent = 0);
    ~Listener();
    void run();

  public slots:
    void stop();
  signals:
    void evdevEvent(quint16 type, quint16 code, qint32 value);
  private:
    int fd;
    bool shouldStop;
  };
}

class QEvdev : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ getPath WRITE setPath)
public:
  explicit QEvdev(QObject *parent = 0);
  explicit QEvdev(QString path, QObject *parent = 0);
  ~QEvdev();

signals:
  void keyEvent(int code, int value);
  void relEvent(int code, int value);
  void absEvent(int code, int value);
  void rawEvent(quint16 type, quint16 code, qint32 value);

public slots:
  void setPath(QString path);
  QString getPath() const;


private slots:
  void onListenerEvent(quint16 type, quint16 code, qint32 value);


private:
  QString path;
  qevdev::Listener* listener;
};

#endif // QEVDEV_H
