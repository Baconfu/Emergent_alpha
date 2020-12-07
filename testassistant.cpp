#include "testassistant.h"

TestAssistant::TestAssistant(World * world)
{
    m_world = world;
}

void TestAssistant::testChunks()
{
    QVector<Chunk*> env = m_world->getEnvironment();
    //qDebug()<<"chunk count: "<<env.length();
    //qDebug()<<"environment: "<<env;
    //qDebug()<<" ";

    for(int i=0; i<env.length(); i++){
        Chunk * c = env[i];
        //qDebug()<<"chunk"<<i;
        //qDebug()<<"position: "<<c->getPosition();

    }
}
