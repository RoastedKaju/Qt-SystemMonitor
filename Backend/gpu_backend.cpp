#include "gpu_backend.h"

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

GPUBackend::GPUBackend(QObject* parent)
{
    m_gpuName = "None";
    m_vendorName = "Unknown";
    m_driverVersion = "Unknown";
    m_memory = 0.0;

    // Get all gpus
    m_gpus = hwinfo::getAllGPUs();
    if(m_gpus.empty())
    {
        qWarning() << "GPU not found";
        return;
    }

    const QString gpuName = QString::fromStdString(m_gpus.at(0).name()).trimmed();
    setGpuName(gpuName);

    const QString vendorName = QString::fromStdString(m_gpus.at(0).vendor()).trimmed();
    setVendorName(vendorName);

    setDriverVersion(QString::fromStdString(m_gpus.at(0).driverVersion()));

    // Get dedicated valid memory
    IDXGIFactory* pFactory = nullptr;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) return;
    IDXGIAdapter* pAdapter = nullptr;
    for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC desc;
        pAdapter->GetDesc(&desc);

        double dedicatedMemory = desc.DedicatedVideoMemory / (1024.0 * 1024.0 * 1024.0);
        if(dedicatedMemory == 0)
        {
            pAdapter->Release();
            continue;
        }

        setMemory(dedicatedMemory);
        pAdapter->Release();
    }
    pFactory->Release();
}

QString GPUBackend::gpuName() const
{
    return m_gpuName;
}

void GPUBackend::setGpuName(const QString &newGpuName)
{
    if (m_gpuName == newGpuName)
        return;
    m_gpuName = newGpuName;
    emit gpuNameChanged();
}

QString GPUBackend::vendorName() const
{
    return m_vendorName;
}

void GPUBackend::setVendorName(const QString &newVendorName)
{
    if (m_vendorName == newVendorName)
        return;
    m_vendorName = newVendorName;
    emit vendorNameChanged();
}

double GPUBackend::memory() const
{
    return m_memory;
}

void GPUBackend::setMemory(double newMemory)
{
    if (qFuzzyCompare(m_memory, newMemory))
        return;
    m_memory = newMemory;
    emit memoryChanged();
}

QString GPUBackend::driverVersion() const
{
    return m_driverVersion;
}

void GPUBackend::setDriverVersion(const QString &newDriverVersion)
{
    if (m_driverVersion == newDriverVersion)
        return;
    m_driverVersion = newDriverVersion;
    emit driverVersionChanged();
}
