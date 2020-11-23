#ifndef CHUNK_H
#define CHUNK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QPoint>
#include <QVector>

#include <air.h>
#include <constants.h>
#include <file.h>
#include <terrain.h>
#include <unitspace.h>


class Chunk: public File
{

public:

    Chunk(QPoint chunkPosition);

    QPoint getPosition(){return m_pos;}

    QVector<UnitSpace*> loadChunkFromFile();
    UnitSpace * loadSpace(QJsonObject j);

    void writeChunkToFile();
    QJsonObject writeSpace(UnitSpace * s);

    void setChunkData(QVector<UnitSpace*> chunk_data);


private:
    QPoint m_pos;

    QVector<UnitSpace*> spaces;

    QString path_temp = "C:\\Users\\lixia\\Documents\\qt_projects\\Emergent_alpha\\data\\chunks\\";

    QJsonObject m_obj;

};

#endif // CHUNK_H
