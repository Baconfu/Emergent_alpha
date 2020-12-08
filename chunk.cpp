#include "chunk.h"

#include <QDir>


Chunk::Chunk(QVector3D chunkPosition)
{
    m_pos = chunkPosition;
}

Chunk::~Chunk()
{
    for(int i=0; i<spaces.length(); i++){
        delete(spaces[i]);
    }
}

QVector<UnitSpace*> Chunk::loadChunkFromFile()
{
    QString file_name = "chunk_" + QString::number(m_pos.x()) + "_" + QString::number(m_pos.y()) + ".json";

    QJsonObject obj = load(QDir::currentPath() + "/data/chunks/" + file_name);
    QJsonArray field = obj["chunk"].toArray();

    for(int i=0; i<field.count(); i++){
        QVector3D localPosition = QVector3D(i % Constants::chunk_width_tiles,int((i % Constants::chunk_layer_count_tiles) / Constants::chunk_width_tiles),int(i/Constants::chunk_layer_count_tiles));

        spaces.append(loadSpace(field[i].toObject(),localPosition + getPosition() * Constants::chunk_width_tiles));
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

UnitSpace * Chunk::loadSpace(QJsonObject j,QVector3D position)
{
    if(j["type"].toString() == "air"){
        return new Air(position);
    }
    if(j["type"].toString() == "terrain"){
        return new Terrain(position);
    }
}

QJsonObject Chunk::writeSpace(UnitSpace * s)
{
    QJsonObject obj;
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

UnitSpace *Chunk::getTile(QVector3D p)
{
    return spaces[Constants::chunk_layer_count_tiles * p.z() + Constants::chunk_width_tiles * p.y() + p.x()];
}

