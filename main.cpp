#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include <coordinate.h>
#include <engine.h>
#include <paintplayeravatar.h>
#include <paintterrain.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    Coordinate c(1,1,2);
    Coordinate b(2,4,5);
    c+=b;
    qDebug()<<c.x();
    QQmlApplicationEngine * engine = new QQmlApplicationEngine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<PaintPlayerAvatar>("Paint",1,0,"PaintAvatar");
    qmlRegisterType<PaintTerrain>("Paint",1,0,"PaintTerrain");

    engine->load(url);




    QQuickWindow * window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
    Engine * e = new Engine(nullptr, engine, window);

    return app.exec();
}
