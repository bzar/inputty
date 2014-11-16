#include "evdevdevicelistmodel.h"
#include <QDir>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

QString const EvdevDeviceListModel::INPUT_DEV_DIR = "/dev/input";

EvdevDeviceListModel::EvdevDeviceListModel(QObject *parent) :
  QAbstractListModel(parent), _watcher(QStringList(INPUT_DEV_DIR)), _devices()
{
  connect(&_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(update()));
  update();
}

QHash<int, QByteArray> EvdevDeviceListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[PathRole] = "path";
  return roles;
}

int EvdevDeviceListModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return _devices.size();
}

QVariant EvdevDeviceListModel::data(const QModelIndex& index, int role) const
{
  EvdevDevice const& device = _devices.at(index.row());
  switch(role)
  {
    case NameRole: return device.name;
    case PathRole: return device.path;
    default: return QVariant();
  }
}

void EvdevDeviceListModel::update()
{
  beginResetModel();

  _devices.clear();

  QDir dir(INPUT_DEV_DIR, "event*", QDir::Name, QDir::System);
  QStringList entries = dir.entryList();

  foreach(QString const entry, entries)
  {
    QString path = dir.absoluteFilePath(entry);
    int fd = open(path.toLocal8Bit(), O_RDONLY | O_NDELAY);
    char buf[256] = { 0 };
    if(fd < 0 || ioctl(fd, EVIOCGNAME(sizeof(buf)), buf) < 0)
      continue;

    QString name(buf);

    EvdevDevice device = { name, path };
    _devices << device;
  }

  endResetModel();
}
