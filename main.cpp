#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtCharts>

#include "systeminfo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
