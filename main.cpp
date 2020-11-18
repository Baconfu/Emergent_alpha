#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include <engine.h>
#include <paintplayeravatar.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintPlayerAvatar>("Paint",1,0,"PaintAvatar");

    QQmlApplicationEngine * engine = new QQmlApplicationEngine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine->load(url);



    QQuickWindow * window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
    Engine * e = new Engine(nullptr, engine, window);

    return app.exec();
}
