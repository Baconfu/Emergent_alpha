#include "chunk.h"

#include <QDir>


Chunk::Chunk(QPoint chunkPosition)
{
    m_pos = chunkPosition;

    QString file_name = "chunk_" + QString::number(chunkPosition.x()) + "_" + QString::number(chunkPosition.y()) + ".json";

    QJsonObject obj = load(QDir::currentPath() + "/data/chunks/" + file_name);
    qDebug()<<QDir::currentPath() + "/data/chunks/" + file_name;
    qDebug()<<obj;
}
