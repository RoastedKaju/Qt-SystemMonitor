#include "systeminfo.h"

#include <QDebug>

#include <windows.h>
#include <psapi.h>

SystemInfo::SystemInfo(QObject* parent) : QObject(parent)
{
    m_cpuUtil = 100;
    m_cpuName = "Default Value";

    connect(&m_timer, &QTimer::timeout, this, &SystemInfo::updateSystemInfo);
    m_timer.start(1000);

    // This will get the CPU name,cores from registry
    setCpuName("NA");
    setLogicalCores(0);
    setMemoryUsed(0);
}

uint32_t SystemInfo::cpuUtil() const
{
    return m_cpuUtil;
}

void SystemInfo::setCpuUtil(uint32_t newCpuUtil)
{
    if (m_cpuUtil == newCpuUtil)
        return;
    m_cpuUtil = newCpuUtil;
    emit cpuUtilChanged();
}

QString SystemInfo::cpuName() const
{
    return m_cpuName;
}

void SystemInfo::setCpuName(const QString &newCpuName)
{
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
        return;

    wchar_t cpuName[256];
    DWORD size = sizeof(cpuName);

    if (RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr, reinterpret_cast<LPBYTE>(cpuName), &size) == ERROR_SUCCESS)
    {
        m_cpuName = m_cpuName = QString::fromWCharArray(cpuName).trimmed();;
        emit cpuNameChanged();
    }

    RegCloseKey(hKey);
}

uint32_t SystemInfo::logicalCores() const
{
    return m_logicalCores;
}

void SystemInfo::setLogicalCores(uint32_t newLogicalCores)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    m_logicalCores = static_cast<uint32_t>(si.dwNumberOfProcessors);

    switch(si.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_INTEL:
        m_architecture = "x86";
        break;
    case PROCESSOR_ARCHITECTURE_AMD64:
        m_architecture = "x64";
        break;
    }

    emit logicalCoresChanged();
}

QString SystemInfo::architecture() const
{
    return m_architecture;
}

uint32_t SystemInfo::cacheSizeL1()
{
    DWORD length = 0;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer = nullptr;
    GetLogicalProcessorInformationEx(RelationCache, nullptr, &length);

    buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)malloc(length);
    if (!buffer) { return 0; }

    if (!GetLogicalProcessorInformationEx(RelationCache, buffer, &length))
    {
        free(buffer);
        return 0;
    }

    BYTE* ptr = (BYTE*)buffer;
    BYTE* end = ptr + length;

    while (ptr < end)
    {
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)ptr;

        if (info->Relationship == RelationCache)
        {
            switch ((int)info->Cache.Level) {
            case 1:
                m_cacheSizeL1 = (uint32_t)info->Cache.CacheSize / 1024;
                break;
            case 2:
                m_cacheSizeL2 = (uint32_t)info->Cache.CacheSize / 1024;
                break;
            case 3:
                m_cacheSizeL3 = (uint32_t)info->Cache.CacheSize / 1024;
                break;
            }
        }

        ptr += info->Size;
    }

    free(buffer);

    return m_cacheSizeL1;
}

uint32_t SystemInfo::cacheSizeL2() const
{
    return m_cacheSizeL2;
}

uint32_t SystemInfo::cacheSizeL3() const
{
    return m_cacheSizeL3;
}

quint64 SystemInfo::memoryUsed() const
{
    return m_memoryUsed;
}

void SystemInfo::setMemoryUsed(quint64 newMemoryUsed)
{
    if (m_memoryUsed == newMemoryUsed)
        return;
    m_memoryUsed = newMemoryUsed;
    emit memoryUsedChanged();
}

void SystemInfo::refreshCpuInfo()
{
    static FILETIME prevIdleTime = {0}, prevKernelTime = {0}, prevUserTime = {0};
    FILETIME idleTime, kernelTime, userTime;

    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime))
        return; // API call failed

    // Convert FILETIME to ULONGLONG
    auto fileTimeToULL = [](const FILETIME &ft)
    {
        return (static_cast<ULONGLONG>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    };

    ULONGLONG idle = fileTimeToULL(idleTime);
    ULONGLONG kernel = fileTimeToULL(kernelTime);
    ULONGLONG user = fileTimeToULL(userTime);

    ULONGLONG prevIdle = fileTimeToULL(prevIdleTime);
    ULONGLONG prevKernel = fileTimeToULL(prevKernelTime);
    ULONGLONG prevUser = fileTimeToULL(prevUserTime);

    ULONGLONG idleDiff = idle - prevIdle;
    ULONGLONG kernelDiff = kernel - prevKernel;
    ULONGLONG userDiff = user - prevUser;

    ULONGLONG total = kernelDiff + userDiff;
    double cpuPercent = total ? (100.0 * (total - idleDiff) / total) : 0.0;

    // Save current values for next call
    prevIdleTime = idleTime;
    prevKernelTime = kernelTime;
    prevUserTime = userTime;

    // Set CPU utilization percent
    setCpuUtil((uint32_t)cpuPercent);
}

void SystemInfo::refreshMemoryInfo()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    // Convert to 64 bit
    quint64 totalGB = totalPhysMem / (1024 * 1024 * 1024);
    quint64 usedGB = physMemUsed / (1024 * 1024 * 1024);

    quint64 loadPercent = (quint64)memInfo.dwMemoryLoad;

    // Comitted memory
    float comitted = static_cast<float>(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / (1024 * 1024 * 1024);

    // Page File
    m_pageFile = QString("%1 / %2")
                     .arg((memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / (1024 * 1024 * 1024))
                    .arg(memInfo.ullTotalPageFile / (1024 * 1024 * 1024));

    setMemoryUsed(usedGB);
    m_totalMemory = totalGB;
    setMemoryLoadPercent(loadPercent);
    setComittedMemory(comitted);
}

void SystemInfo::updateSystemInfo()
{
    refreshCpuInfo();
    refreshMemoryInfo();
}

quint64 SystemInfo::totalMemory() const
{
    return m_totalMemory;
}

quint64 SystemInfo::memoryLoadPercent() const
{
    return m_memoryLoadPercent;
}

void SystemInfo::setMemoryLoadPercent(quint64 newMemoryLoadPercent)
{
    if (m_memoryLoadPercent == newMemoryLoadPercent)
        return;
    m_memoryLoadPercent = newMemoryLoadPercent;
    emit memoryLoadPercentChanged();
}

float SystemInfo::comittedMemory() const
{
    return m_comittedMemory;
}

void SystemInfo::setComittedMemory(float newComittedMemory)
{
    if (qFuzzyCompare(m_comittedMemory, newComittedMemory))
        return;
    m_comittedMemory = newComittedMemory;
    emit comittedMemoryChanged();
}

QString SystemInfo::pageFile() const
{
    return m_pageFile;
}
