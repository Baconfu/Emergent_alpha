#ifndef CHUNK_H
#define CHUNK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QPoint>

#include <file.h>
#include <unitspace.h>


class Chunk: public File
{

public:

    Chunk(QPoint chunkPosition);

    QPoint getPosition(){return m_pos;}


private:
    QPoint m_pos;




};

#endif // CHUNK_H
