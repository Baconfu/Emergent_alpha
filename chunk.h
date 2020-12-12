#ifndef CHUNK_H
#define CHUNK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QPoint>
#include <QVector>
#include <QVector3D>

#include <air.h>
#include <constants.h>
#include <file.h>
#include <terrain.h>
#include <unitspace.h>


class Chunk: public File
{

public:

    Chunk(QVector3D chunkPosition);
    ~Chunk();

    QVector3D getPosition(){return m_pos;}

    QVector<UnitSpace*> loadChunkFromFile();
    UnitSpace * loadSpace(QJsonObject j,QVector3D position);

    void writeChunkToFile();
    QJsonObject writeSpace(UnitSpace * s);

    void setChunkData(QVector<UnitSpace*> chunk_data);

    UnitSpace * getTile(QVector3D p);


    void destroy();
private:
    QVector3D m_pos;

    QVector<UnitSpace*> spaces;

    QString path_temp = "D:\\Qt\\build-Emergent_alpha-Desktop_Qt_5_12_0_MinGW_64_bit-Debug\\data\\chunks";

    QJsonObject m_obj;

};

#endif // CHUNK_H
