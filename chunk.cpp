#include "chunk.h"

#include <QDir>


Chunk::Chunk(QPoint chunkPosition)
{
    m_pos = chunkPosition;


}

QVector<UnitSpace*> Chunk::loadChunkFromFile()
{
    QString file_name = "chunk_" + QString::number(m_pos.x()) + "_" + QString::number(m_pos.y()) + ".json";

    QJsonObject obj = load(QDir::currentPath() + "/data/chunks/" + file_name);
    QJsonArray field = obj["chunk"].toArray();

    for(int i=0; i<field.count(); i++){
        spaces.append(loadSpace(field[i].toObject()));
    }

    return spaces;
}


void Chunk::writeChunkToFile()
{
    QJsonArray field;

    for(int i=0; i<spaces.length(); i++){
        field.append(writeSpace(spaces[i]));
    }
    QJsonObject obj;
    obj["chunk"] = field;

    QString file_name = "chunk_" + QString::number(m_pos.x()) + "_" + QString::number(m_pos.y()) + ".json";
    write(QDir::currentPath() + "/data/chunks/" + file_name,obj);

}

UnitSpace * Chunk::loadSpace(QJsonObject j)
{
    if(j["type"].toString() == "air"){
        return new Air();
    }
    if(j["type"].toString() == "terrain"){
        return new Terrain();
    }
}

QJsonObject Chunk::writeSpace(UnitSpace * s)
{
    QJsonObject obj;
    qDebug()<<s;
    if(typeid (*s) == typeid (Air)){
        obj["type"] = "air";
    }
    if(typeid (*s) == typeid (Terrain)){
        obj["type"] = "terrain";
    }

    return obj;
}

void Chunk::setChunkData(QVector<UnitSpace*> chunk_data)
{
    spaces = chunk_data;
}
