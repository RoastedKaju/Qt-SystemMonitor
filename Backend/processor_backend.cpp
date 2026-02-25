#include "processor_backend.h"

ProcessorBackend::ProcessorBackend(QObject* parent)
{
    // Default values
    m_processorName = "Default Value";
    m_architecture = "Default Value";
    m_cpuUtilHistory.fill(0.0, 60);
    m_clockSpeed = 0.0;

    PdhOpenQuery(nullptr, 0, &m_pdhQuery);
    PdhAddEnglishCounter(m_pdhQuery, L"\\Processor(_Total)\\% Processor Time", 0, &m_pdhCounter);
    PdhCollectQueryData(m_pdhQuery); // first call primes it, always returns 0

    // Get CPU name from HWINFO
    m_processors = hwinfo::getAllCPUs();
    if(m_processors.empty())
    {
        qCritical() << "Could not get processor\n";
        return;
    }

    QString procName = QString::fromStdString(m_processors.at(0).modelName());
    procName = procName.trimmed(); // remove spaces
    setProcessorName(procName);

    // Get CPU architecture
    QString arch = (sizeof(void*) == 8) ? "x64" : "x86";
    setArchitecture(arch);

    // Get logical cores
    setLogicalCores(m_processors.at(0).numLogicalCores());
    // Get physical cores
    setPhysicalCores(m_processors.at(0).numPhysicalCores());

    // Get cache sizes
    const int l1Cache = m_processors.at(0).L1CacheSize_Bytes();
    const int l2Cache = m_processors.at(0).L2CacheSize_Bytes() / 1024;
    const int l3Cache = m_processors.at(0).L3CacheSize_Bytes() / 1024;
    setCacheSizes({l1Cache, l2Cache, l3Cache});

    // Start timer for getting CPU Util
    connect(&m_updateTimer, &QTimer::timeout, this, &ProcessorBackend::updateInfo);
    m_updateTimer.start(1000);

    // Get max clock speed
    double clockSpeed = m_processors.at(0).maxClockSpeed_MHz() / 1000.0;
    setClockSpeed(clockSpeed);
}

ProcessorBackend::~ProcessorBackend()
{
    PdhCloseQuery(m_pdhQuery);
}

QString ProcessorBackend::processorName() const
{
    return m_processorName;
}

void ProcessorBackend::setProcessorName(const QString &newProcessorName)
{
    if (m_processorName == newProcessorName)
        return;
    m_processorName = newProcessorName;
    emit processorNameChanged();
}

QString ProcessorBackend::architecture() const
{
    return m_architecture;
}

void ProcessorBackend::setArchitecture(const QString &newArchitecture)
{
    if (m_architecture == newArchitecture)
        return;
    m_architecture = newArchitecture;
    emit architectureChanged();
}

int ProcessorBackend::logicalCores() const
{
    return m_logicalCores;
}

void ProcessorBackend::setLogicalCores(int newLogicalCores)
{
    if (m_logicalCores == newLogicalCores)
        return;
    m_logicalCores = newLogicalCores;
    emit logicalCoresChanged();
}

int ProcessorBackend::physicalCores() const
{
    return m_physicalCores;
}

void ProcessorBackend::setPhysicalCores(int newPhysicalCores)
{
    if (m_physicalCores == newPhysicalCores)
        return;
    m_physicalCores = newPhysicalCores;
    emit physicalCoresChanged();
}

QList<int> ProcessorBackend::cacheSizes() const
{
    return m_cacheSizes;
}

void ProcessorBackend::setCacheSizes(const QList<int> &newCacheSizes)
{
    if (m_cacheSizes == newCacheSizes)
        return;
    m_cacheSizes = newCacheSizes;
    emit cacheSizesChanged();
}

QList<double> ProcessorBackend::cpuUtilHistory() const
{
    return m_cpuUtilHistory;
}

void ProcessorBackend::setCpuUtilHistory(const QList<double> &newCpuUtilHistory)
{
    if (m_cpuUtilHistory == newCpuUtilHistory)
        return;
    m_cpuUtilHistory = newCpuUtilHistory;
    emit cpuUtilHistoryChanged();
}

double ProcessorBackend::clockSpeed() const
{
    return m_clockSpeed;
}

void ProcessorBackend::setClockSpeed(double newClockSpeed)
{
    if (qFuzzyCompare(m_clockSpeed, newClockSpeed))
        return;
    m_clockSpeed = newClockSpeed;
    emit clockSpeedChanged();
}

void ProcessorBackend::updateInfo()
{
    PDH_FMT_COUNTERVALUE value;
    PdhCollectQueryData(m_pdhQuery);
    PdhGetFormattedCounterValue(m_pdhCounter, PDH_FMT_DOUBLE, nullptr, &value);

    m_cpuUtilHistory.removeFirst();
    m_cpuUtilHistory.append(value.doubleValue);
    emit cpuUtilHistoryChanged();
}
