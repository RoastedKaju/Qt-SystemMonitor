#include "memory_backend.h"

MemoryBackend::MemoryBackend(QObject* parent)
{
    m_totalMemory = 0.0;
    m_usedMemory = 0.0;
    m_freeMemory = 0.0;

    setTotalMemory(m_memory.total_Bytes()/ (1024 * 1024 * 1024));

    // Set update timer
    connect(&m_timer, &QTimer::timeout, this, &MemoryBackend::updateInfo);
    m_timer.start(1000);

    // Get memory module information
    std::vector<hwinfo::Memory::Module> modules = m_memory.modules();
    QVariantList list;
    for (const auto& module : modules)
    {
        QVariantMap map;
        map["vendor"] = QString::fromStdString(module.vendor).trimmed();
        map["name"] = QString::fromStdString(module.name).trimmed();
        map["total_Bytes"] = module.total_Bytes / (1024 * 1024 * 1024);
        list << map;
    }
    setVendorInfo(list);
}

double MemoryBackend::totalMemory() const
{
    return m_totalMemory;
}

void MemoryBackend::setTotalMemory(double newTotalMemory)
{
    if (qFuzzyCompare(m_totalMemory, newTotalMemory))
        return;
    m_totalMemory = newTotalMemory;
    emit totalMemoryChanged();
}

double MemoryBackend::usedMemory() const
{
    return m_usedMemory;
}

void MemoryBackend::setUsedMemory(double newUsedMemory)
{
    if (qFuzzyCompare(m_usedMemory, newUsedMemory))
        return;
    m_usedMemory = newUsedMemory;
    emit usedMemoryChanged();
}

double MemoryBackend::freeMemory() const
{
    return m_freeMemory;
}

void MemoryBackend::setFreeMemory(double newFreeMemory)
{
    if (qFuzzyCompare(m_freeMemory, newFreeMemory))
        return;
    m_freeMemory = newFreeMemory;
    emit freeMemoryChanged();
}

QVariantList MemoryBackend::vendorInfo() const
{
    return m_vendorInfo;
}

void MemoryBackend::setVendorInfo(const QVariantList &newVendorInfo)
{
    if (m_vendorInfo == newVendorInfo)
        return;
    m_vendorInfo = newVendorInfo;
    emit vendorInfoChanged();
}

void MemoryBackend::updateInfo()
{
    const double usedMemory = m_memory.total_Bytes() - m_memory.available_Bytes();
    setUsedMemory(usedMemory / (1024.0 * 1024.0 * 1024.0));

    const double freeMemory = m_memory.free_Bytes() / (1024.0 * 1024.0 * 1024.0);
    setFreeMemory(freeMemory);
}

