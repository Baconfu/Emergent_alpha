#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QPointer>
#include <QSharedPointer>

#include <engine.h>
#include <paintgrid.h>
#include <paintplayeravatar.h>
#include <paintterrain.h>
#include <paintladder.h>
#include <terraingeneration.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QSharedPointer<QQmlApplicationEngine> engine = QSharedPointer<QQmlApplicationEngine>(new QQmlApplicationEngine);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine.data(), &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<PaintGrid>("Paint",1,0,"PaintGrid");
    qmlRegisterType<PaintPlayer>("Paint",1,0,"PaintPlayer");
    qmlRegisterType<PaintTerrain>("Paint",1,0,"PaintTerrain");
    qmlRegisterType<PaintLadder>("Paint",1,0,"PaintLadder");
    qmlRegisterType<TerrainGeneration>("Paint",1,0,"TerrainGeneration");
    engine->load(url);


    QSharedPointer<QQuickWindow> window = QSharedPointer<QQuickWindow>(qobject_cast<QQuickWindow*>(engine->rootObjects().at(0)));
    Engine e(nullptr, engine.data(), window.data());

    return app.exec();
}
