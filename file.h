#ifndef FILE_H
#define FILE_H

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>


class File
{
public:
    File();

    QJsonObject load(QString path);
    void write(QString path,QJsonObject obj);
};

#endif // FILE_H
