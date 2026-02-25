#ifndef MEMORY_BACKEND_H
#define MEMORY_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QTimer>

#include <hwinfo/hwinfo.h>

class MemoryBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit MemoryBackend(QObject* parent = nullptr);

    Q_PROPERTY(double totalMemory READ totalMemory WRITE setTotalMemory NOTIFY totalMemoryChanged FINAL)
    double totalMemory() const;
    void setTotalMemory(double newTotalMemory);

    Q_PROPERTY(double usedMemory READ usedMemory WRITE setUsedMemory NOTIFY usedMemoryChanged FINAL)
    double usedMemory() const;
    void setUsedMemory(double newUsedMemory);

    Q_PROPERTY(double freeMemory READ freeMemory WRITE setFreeMemory NOTIFY freeMemoryChanged FINAL)
    double freeMemory() const;
    void setFreeMemory(double newFreeMemory);

    Q_PROPERTY(QVariantList vendorInfo READ vendorInfo WRITE setVendorInfo NOTIFY vendorInfoChanged FINAL)
    QVariantList vendorInfo() const;
    void setVendorInfo(const QVariantList &newVendorInfo);

signals:
    void totalMemoryChanged();
    void usedMemoryChanged();
    void freeMemoryChanged();
    void vendorInfoChanged();

public slots:
    void updateInfo();

private:
    hwinfo::Memory m_memory;
    double m_totalMemory;
    QTimer m_timer;
    double m_usedMemory;
    double m_freeMemory;
    QVariantList m_vendorInfo;
};

#endif // MEMORY_BACKEND_H
