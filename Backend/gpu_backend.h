#ifndef GPU_BACKEND_H
#define GPU_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

#include <hwinfo/hwinfo.h>
#include <vector>

class GPUBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit GPUBackend(QObject* parent = nullptr);

    Q_PROPERTY(QString gpuName READ gpuName WRITE setGpuName NOTIFY gpuNameChanged FINAL)
    QString gpuName() const;
    void setGpuName(const QString &newGpuName);

    Q_PROPERTY(QString vendorName READ vendorName WRITE setVendorName NOTIFY vendorNameChanged FINAL)
    QString vendorName() const;
    void setVendorName(const QString &newVendorName);

    Q_PROPERTY(double memory READ memory WRITE setMemory NOTIFY memoryChanged FINAL)
    double memory() const;
    void setMemory(double newMemory);

    Q_PROPERTY(QString driverVersion READ driverVersion WRITE setDriverVersion NOTIFY driverVersionChanged FINAL)
    QString driverVersion() const;
    void setDriverVersion(const QString &newDriverVersion);

signals:
    void gpuNameChanged();
    void vendorNameChanged();
    void memoryChanged();

    void driverVersionChanged();

private:
    std::vector<hwinfo::GPU> m_gpus;
    QString m_gpuName;
    QString m_vendorName;
    double m_memory;
    QString m_driverVersion;
};

#endif // GPU_BACKEND_H
