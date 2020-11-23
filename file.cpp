#include "file.h"

File::File()
{

}

QJsonObject File::load(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    QJsonDocument loadData(QJsonDocument::fromJson(data));
    qDebug()<<loadData;

    return loadData.object();
}
