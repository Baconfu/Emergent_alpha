#include "paintladder.h"
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QImage>
#include <math.h>

PaintLadder::PaintLadder(QQuickItem *parent):
    QQuickPaintedItem (parent)
{

}

PaintLadder::~PaintLadder()
{

}

void PaintLadder::paint(QPainter *painter)
{
    //QRect r = QRect(QPoint(0,0),QPoint(100,100));
    //painter->fillRect(r,QColor(200,200,200));

    int stepCount = 3;
    int stepHeight = 2;
    QColor ladderColor = QColor(0,100,250);

    qDebug()<<m_rotation;
    if (m_rotation == 0){
        qDebug()<<"entering painting loop";
        for (int i=0 ; i<stepCount ; i++){
            QRect r = QRect(QPoint(5,i*stepHeight*2),QPoint(25,i*stepHeight*2+stepHeight));
            painter->fillRect(r,ladderColor);
            //painter->drawRect(r);
            qDebug()<<"Drawn ladder in rotation 0";
        }
    }
    else if (m_rotation == 1) {

    }
    else if (m_rotation == 2) {
        QRect r = QRect(QPoint(5,28),QPoint(25,30));
        painter->fillRect(r,ladderColor);
        //painter->drawRect(r);
        qDebug()<<"Drawn ladder in rotation 2";
    }
    else if (m_rotation == 3) {

    }



}
