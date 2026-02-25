#ifndef ETHERNET_BACKEND_H
#define ETHERNET_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QTimer>

class EthernetBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit EthernetBackend(QObject* parent = nullptr);

    Q_PROPERTY(quint64 downloadSpeed READ downloadSpeed WRITE setDownloadSpeed NOTIFY downloadSpeedChanged FINAL)
    quint64 downloadSpeed() const;
    void setDownloadSpeed(quint64 newDownloadSpeed);

public slots:
    void onUpdate();

signals:
    void downloadSpeedChanged();
    void uploadSpeedChanged();

private:
    QTimer m_timer;
    quint64 m_downloadSpeed;
    quint64 m_prevBytesReceived;
};

#endif // ETHERNET_BACKEND_H
