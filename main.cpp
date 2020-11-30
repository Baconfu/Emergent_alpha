#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include <engine.h>
#include <paintgrid.h>
#include <paintplayeravatar.h>
#include <paintterrain.h>
#include <paintuibase.h>
#include <terraingeneration.h>n


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
    qmlRegisterType<PaintPlayerAvatar>("Paint",1,0,"PaintAvatar");
    qmlRegisterType<PaintTerrain>("Paint",1,0,"PaintTerrain");
    qmlRegisterType<PaintUIBase>("Paint",1,0,"PaintUiBase");
    qmlRegisterType<TerrainGeneration>("Paint",1,0,"TerrainGeneration");

    engine->load(url);




    QQuickWindow * window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
    Engine * e = new Engine(nullptr, engine, window);

    return app.exec();
}
