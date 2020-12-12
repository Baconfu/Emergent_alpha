#include "paintladder.h"
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QImage>
#include <math.h>

PaintLadder::PaintLadder(QQuickItem *parent):
    QQuickPaintedItem (parent)
{
    QString path = (QDir::currentPath() + "/data/sprites/ladder.png");
    qDebug()<<path;
    src.load(QDir::currentPath() + "/data/sprites/ladder.png");
    qDebug()<<src;
}

PaintLadder::~PaintLadder()
{

}

void PaintLadder::paint(QPainter *painter)
{

    QRectF frame = QRectF(2,0,size().width(),size().height());
    painter->drawImage(frame,src);


    /*
    int stepCount = 3;
    float stepHeight = 2.5;
    QColor ladderColor = QColor(0,100,250);


    if (m_painted_rotation == 0){
        for (int i=0 ; i<stepCount ; i++){
            QRect r = QRect(QPoint(5,i*stepHeight*2),QPoint(25,i*stepHeight*2+stepHeight));
            painter->fillRect(r,ladderColor);

        }
    }
    else if (m_painted_rotation == 1) {

    }
    else if (m_painted_rotation == 2) {
        QRect r = QRect(QPoint(5,24),QPoint(25,30));
        painter->fillRect(r,ladderColor);
    }
    else if (m_painted_rotation == 3) {

    }*/





}
