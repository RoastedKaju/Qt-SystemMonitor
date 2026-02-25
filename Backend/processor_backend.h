#ifndef PROCESSOR_BACKEND_H
#define PROCESSOR_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <QLineSeries>

#include <vector>
#include <hwinfo/hwinfo.h>
#include <windows.h>
#include <pdh.h>
#pragma comment(lib, "pdh.lib")

class ProcessorBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit ProcessorBackend(QObject* parent = nullptr);
    ~ProcessorBackend();

    Q_PROPERTY(QString processorName READ processorName WRITE setProcessorName NOTIFY processorNameChanged FINAL)
    QString processorName() const;
    void setProcessorName(const QString &newProcessorName);

    Q_PROPERTY(QString architecture READ architecture WRITE setArchitecture NOTIFY architectureChanged FINAL)
    QString architecture() const;
    void setArchitecture(const QString &newArchitecture);

    Q_PROPERTY(int logicalCores READ logicalCores WRITE setLogicalCores NOTIFY logicalCoresChanged FINAL)
    int logicalCores() const;
    void setLogicalCores(int newLogicalCores);

    Q_PROPERTY(int physicalCores READ physicalCores WRITE setPhysicalCores NOTIFY physicalCoresChanged FINAL)
    int physicalCores() const;
    void setPhysicalCores(int newPhysicalCores);

    Q_PROPERTY(QList<int> cacheSizes READ cacheSizes WRITE setCacheSizes NOTIFY cacheSizesChanged FINAL)
    QList<int> cacheSizes() const;
    void setCacheSizes(const QList<int> &newCacheSizes);

    Q_PROPERTY(QList<double> cpuUtilHistory READ cpuUtilHistory WRITE setCpuUtilHistory NOTIFY cpuUtilHistoryChanged FINAL)
    QList<double> cpuUtilHistory() const;
    void setCpuUtilHistory(const QList<double> &newCpuUtilHistory);

    Q_PROPERTY(double clockSpeed READ clockSpeed WRITE setClockSpeed NOTIFY clockSpeedChanged FINAL)
    double clockSpeed() const;
    void setClockSpeed(double newClockSpeed);

signals:
    void processorNameChanged();
    void architectureChanged();
    void logicalCoresChanged();
    void physicalCoresChanged();
    void cacheSizesChanged();
    void cpuUtilHistoryChanged();
    void clockSpeedChanged();

public slots:
    void updateInfo();

private:
    QTimer m_updateTimer;
    QString m_processorName;
    QString m_architecture;
    int m_logicalCores;
    int m_physicalCores;
    QList<int> m_cacheSizes;
    QList<double> m_cpuUtilHistory;
    std::vector<hwinfo::CPU> m_processors;
    double m_clockSpeed;

    PDH_HQUERY m_pdhQuery;
    PDH_HCOUNTER m_pdhCounter;
};

#endif // PROCESSOR_BACKEND_H
