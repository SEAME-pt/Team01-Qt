#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QRandomGenerator>
#include <iostream>
#include "radialbar.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    // If the QML loaded successfully, start a timer to push random speeds
    if (!engine.rootObjects().isEmpty()) {
        QObject *root = engine.rootObjects().first();

        QTimer *timer = new QTimer(&app);
        QObject::connect(timer, &QTimer::timeout, [root]() {
            int speed = QRandomGenerator::global()->bounded(0, 301);
            // Set the property on the root QML object: 'currentSpeed'
            root->setProperty("currentSpeed", speed);
        });
        timer->start(800); // update every 800 ms
    }

    return app.exec();
}
