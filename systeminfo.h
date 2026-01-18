#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>
#include <QTimer>

class SystemInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString memoryInfo READ memoryInfo NOTIFY memoryInfoChanged)
    Q_PROPERTY(QString cpuInfo READ cpuInfo NOTIFY cpuInfoChanged)

public:
    explicit SystemInfo(QObject* parent = nullptr);

    QString memoryInfo() const;
    QString cpuInfo() const;

signals:
    void memoryInfoChanged();
    void cpuInfoChanged();

public slots:
    void onButtonClicked();
    void updateMemoryInfo();
    void updateCpuInfo();

private:
    QTimer timer;
    QString m_memoryInfo = QString("Init...");
    QString m_cpuInfo = QString("Init...");
};

#endif // SYSTEMINFO_H
