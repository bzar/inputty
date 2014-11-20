#ifndef EVDEVDEVICELISTMODEL_H
#define EVDEVDEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>

class EvdevDeviceListModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(int length READ rowCount NOTIFY lengthChanged)
public:
  explicit EvdevDeviceListModel(QObject *parent = 0);
  enum EvdevDeviceRoles {
    NameRole = Qt::UserRole + 1,
    PathRole,
  };
  QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  Q_INVOKABLE QVariant get(int index);

signals:
  void lengthChanged(int);

public slots:

private slots:
  void update();

private:
  struct EvdevDevice
  {
    QString name;
    QString path;
  };
  static QString const INPUT_DEV_DIR;
  QFileSystemWatcher _watcher;
  QList<EvdevDevice> _devices;
};

#endif // EVDEVDEVICELISTMODEL_H
