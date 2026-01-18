#include "systeminfo.h"

#include <QDebug>

#include <windows.h>
#include <psapi.h>

SystemInfo::SystemInfo(QObject* parent) : QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, &SystemInfo::updateMemoryInfo);
    connect(&timer, &QTimer::timeout, this, &SystemInfo::updateCpuInfo);
    timer.start(1000);
}

QString SystemInfo::memoryInfo() const
{
    return m_memoryInfo;
}

QString SystemInfo::cpuInfo() const
{
    return m_cpuInfo;
}

void SystemInfo::onButtonClicked()
{
    qDebug() << "Button Clicked! Function executed in C++.";
}

void SystemInfo::updateMemoryInfo()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    // Convert to 64 bit
    quint64 totalMB = totalPhysMem / (1024 * 1024);
    quint64 usedMB = physMemUsed / (1024 * 1024);

    QString info = QString("%1 / %2 MB")
                       .arg(usedMB)
                       .arg(totalMB);

    if(info != m_memoryInfo)
    {
        m_memoryInfo = info;
        emit memoryInfoChanged();
    }
}

void SystemInfo::updateCpuInfo()
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

    QString info = QString("CPU: %1 %").arg(cpuPercent, 0, 'f', 1);

    if (info != m_cpuInfo)
    {
        m_cpuInfo = info;
        emit cpuInfoChanged();
    }
}
