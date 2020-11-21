#include "file.h"

File::File()
{

}

QJsonObject File::load(QString path)
{
    QFile file(QString("C:/Users/lixia/Documents/qt_projects/Pavement1.1/saves"));
    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    QJsonDocument loadData(QJsonDocument::fromJson(data));
    qDebug()<<loadData;

    return loadData.object();
}
