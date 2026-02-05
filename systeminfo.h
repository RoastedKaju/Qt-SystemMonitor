#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>
#include <QTimer>
#include <QQmlEngine>

class SystemInfo : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit SystemInfo(QObject* parent = nullptr);

    // CPU Properties
    Q_PROPERTY(uint32_t cpuUtil READ cpuUtil WRITE setCpuUtil NOTIFY cpuUtilChanged FINAL)
    uint32_t cpuUtil() const;
    void setCpuUtil(uint32_t newCpuUtil);

    Q_PROPERTY(QString cpuName READ cpuName WRITE setCpuName NOTIFY cpuNameChanged FINAL)
    QString cpuName() const;
    void setCpuName(const QString &newCpuName);

    Q_PROPERTY(uint32_t logicalCores READ logicalCores WRITE setLogicalCores NOTIFY logicalCoresChanged FINAL)
    uint32_t logicalCores() const;
    void setLogicalCores(uint32_t newLogicalCores);

    // Also handled in logical cores property
    Q_PROPERTY(QString architecture READ architecture CONSTANT)
    Q_PROPERTY(uint32_t cacheSizeL1 READ cacheSizeL1 CONSTANT)
    Q_PROPERTY(uint32_t cacheSizeL2 READ cacheSizeL2 CONSTANT)
    Q_PROPERTY(uint32_t cacheSizeL3 READ cacheSizeL3 CONSTANT)


    // RAM Properties
    Q_PROPERTY(quint64 memoryUsed READ memoryUsed WRITE setMemoryUsed NOTIFY memoryUsedChanged FINAL)
    quint64 memoryUsed() const;
    void setMemoryUsed(quint64 newMemoryUsed);

    Q_PROPERTY(quint64 totalMemory READ totalMemory CONSTANT)
    Q_PROPERTY(quint64 memoryLoadPercent READ memoryLoadPercent WRITE setMemoryLoadPercent NOTIFY memoryLoadPercentChanged FINAL)
    quint64 memoryLoadPercent() const;
    void setMemoryLoadPercent(quint64 newMemoryLoadPercent);

    Q_PROPERTY(float comittedMemory READ comittedMemory WRITE setComittedMemory NOTIFY comittedMemoryChanged FINAL)
    float comittedMemory() const;
    void setComittedMemory(float newComittedMemory);

    Q_PROPERTY(QString pageFile READ pageFile CONSTANT)

    void refreshCpuInfo();
    void refreshMemoryInfo();

    // Getter functions
    QString architecture() const;
    uint32_t cacheSizeL1();
    uint32_t cacheSizeL2() const;
    uint32_t cacheSizeL3() const;
    quint64 totalMemory() const;
    QString pageFile() const;

signals:
    void cpuUtilChanged();
    void cpuNameChanged();

    void logicalCoresChanged();

    void memoryUsedChanged();

    void memoryLoadPercentChanged();

    void comittedMemoryChanged();

public slots:
    void updateSystemInfo();

private:
    QTimer m_timer;
    // CPU variables
    uint32_t m_cpuUtil;
    QString m_cpuName;
    uint32_t m_logicalCores;
    QString m_architecture;
    uint32_t m_cacheSizeL1;
    uint32_t m_cacheSizeL2;
    uint32_t m_cacheSizeL3;
    uint32_t m_memoryUsed;
    quint64 m_totalMemory;
    quint64 m_memoryLoadPercent;
    float m_comittedMemory;
    QString m_pageFile;
};

#endif // SYSTEMINFO_H
