#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include <engine.h>
#include <paintgrid.h>
#include <paintplayeravatar.h>
#include <paintterrain.h>
#include <paintladder.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine * engine = new QQmlApplicationEngine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<PaintGrid>("Paint",1,0,"PaintGrid");
    qmlRegisterType<PaintPlayer>("Paint",1,0,"PaintPlayer");
    qmlRegisterType<PaintTerrain>("Paint",1,0,"PaintTerrain");
    qmlRegisterType<PaintLadder>("Paint",1,0,"PaintLadder");

    engine->load(url);




    QQuickWindow * window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
    Engine * e = new Engine(nullptr, engine, window);

    return app.exec();
}
