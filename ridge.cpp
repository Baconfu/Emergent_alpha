#include "ridge.h"

#include <QDebug>

Ridge::Ridge(Hex * origin, Hex * destination, QRandomGenerator * generator)
{
    gen = generator;

    m_origin = origin;
    m_destination = destination;
}

void Ridge::createPath()
{
    QVector<QPointF> ridge;
    QVector2D origin = QVector2D(m_origin->getFocalPoint());
    QVector2D destination = QVector2D(m_destination->getFocalPoint());
    ridge.append(origin.toPointF());

    QVector2D vector = rotateVector(destination - origin,(gen->generate()%1000-500) / 3000);

    float initialLength = (destination-origin).length();
    float cumulativeLength = 0;
    int i = 0;
    while(true){

        if(i>1000){
            break;
        }

        int rand = gen->generate64()%1000;
        float angle = (rand - 500);
        angle = angle / 2000;


        vector.normalize();
        QVector2D dest = QVector2D(destination.toPointF() - ridge[i]);
        if(dest.length()<initialLength/6){
            angle /= ((initialLength/5-dest.length())/10);
        }
        if(dest.length()<10){
            ridge.append(destination.toPointF());
            break;
        }
        if(!dest.isNull()){
            float tendency = getVectorAngle(dest) - getVectorAngle(vector);
            if(tendency>3.1415926){
                tendency -= 3.1415926 * 2;

            }
            if(tendency<-3.1415926){
                tendency+=2 * 3.1415926;
            }


            if(cumulativeLength < initialLength/2){
                tendency/=10;
            }
            angle+=tendency/5;
            //qDebug()<<tendency;

        }

        vector = rotateVector(vector,angle);

        int length = (gen->generate64()%10+10)/5;
        length *= initialLength/565;
        cumulativeLength += length;

        ridge.append(ridge[i]+length*vector.toPointF());

        i+=1;
    }
    path = ridge;
}


QVector2D Ridge::rotateVector(QVector2D vector, float angle)
{
    return QVector2D(float(vector.length())*cos(getVectorAngle(vector)+angle),
                     float(vector.length())*sin(getVectorAngle(vector)+angle));
}

float Ridge::getVectorAngle(QVector2D vector)
{
    float angle = atan(vector.y()/vector.x());
    if(vector.x()<0){
        angle += 3.1415926;
    }else{
        if(vector.y()<0){
            angle += 2*3.1415926;
        }
    }
    return angle;
}
