#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "systeminfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    SystemInfo monitorSystemInfo;
    engine.rootContext()->setContextProperty("monitorSystemInfo", &monitorSystemInfo);

    engine.loadFromModule("SystemMonitor", "Main");
    return app.exec();
}
