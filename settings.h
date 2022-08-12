#ifndef MACHINESETTINGS_H
#define MACHINESETTINGS_H

#include <QMap>
#include <QDebug>

#include <QAbstractListModel>


// class MachineSettings : public QObject, public QVariantMap // <QString, QString> // QObject
class MachineSettings : public QAbstractListModel
{
    Q_OBJECT

public:
    MachineSettings();

    //QString operator[](const QString &key){ return this[key]; };

    void insert(QString &key, QString &value);
    Q_INVOKABLE QString get(QString key){ return _settings[key]; };

    // con QVariantMap -- Q_INVOKABLE QString get(QString key){ return this->value(key).toString(); };

    // con QAbstractListModel
    int rowCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        qDebug() << "[rowCount] return: " << _settings.count();
        return _settings.count();
    };

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const
    {
        qDebug() << "[data] " << index.row() << " - " << role;
        return QVariant("**");
    };


    // Un QVariant può essere usato con oggetto Javascript in QML
    Q_INVOKABLE QVariantMap getObjMap() {
            QVariantMap rval;
            foreach (QString key, _settings.keys()) {
                // TODO: make sure all QObject subclasses are exported to QML
                rval[key] = QVariant::fromValue<QString>(_settings[key]);
            }
            return rval;
        }

private:
    QMap<QString, QString> _settings;
};

#endif // MACHINESETTINGS_H
