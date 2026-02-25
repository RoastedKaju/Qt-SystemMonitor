#include "ethernet_backend.h"

#include <winsock2.h>
#include <windows.h>
#include <psapi.h>
#include <iphlpapi.h>

EthernetBackend::EthernetBackend(QObject* parent)
{
    m_prevBytesReceived = 0;
    m_downloadSpeed = 0;

    connect(&m_timer, &QTimer::timeout, this, &EthernetBackend::onUpdate);
    m_timer.start(1000);
}

void EthernetBackend::onUpdate()
{
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    GetIfTable(NULL, &dwSize, FALSE);
    PMIB_IFTABLE pIfTable = (PMIB_IFTABLE)malloc(dwSize);

    if (pIfTable != NULL) {
        dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);

        if (dwRetVal == NO_ERROR) {
            quint64 totalBytesReceived = 0;

            // Sum up bytes received from all active network interfaces
            for (DWORD i = 0; i < pIfTable->dwNumEntries; i++) {
                MIB_IFROW* pIfRow = &pIfTable->table[i];

                // Only count operational interfaces (status 1 = connected)
                if (pIfRow->dwOperStatus == MIB_IF_OPER_STATUS_OPERATIONAL ||
                    pIfRow->dwOperStatus == MIB_IF_OPER_STATUS_CONNECTED) {
                    totalBytesReceived += pIfRow->dwInOctets;
                }
            }

            // Calculate speed in MB/s (timer runs every 1 second)
            if (m_prevBytesReceived > 0) {
                quint64 bytesReceived = totalBytesReceived - m_prevBytesReceived;

                // Convert to MB/s (bytes received in 1 second / 1024 / 1024)
                double speedMBps = bytesReceived / (1024.0 * 1024.0);
                setDownloadSpeed(speedMBps);
            }

            m_prevBytesReceived = totalBytesReceived;
        }

        free(pIfTable);
    }
}

quint64 EthernetBackend::downloadSpeed() const
{
    return m_downloadSpeed;
}

void EthernetBackend::setDownloadSpeed(quint64 newDownloadSpeed)
{
    if (m_downloadSpeed == newDownloadSpeed)
        return;
    m_downloadSpeed = newDownloadSpeed;
    emit downloadSpeedChanged();
}
