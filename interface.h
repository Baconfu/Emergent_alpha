#ifndef INTERFACE_H
#define INTERFACE_H

#include <QQuickItem>

class Interface: public QQuickItem
{
    Q_OBJECT
public:
    Interface(QQuickItem * parent = nullptr);


    void assignBase(QQuickItem * obj);
    QQuickItem * getBase(){return m_base;}

protected:


    QQuickItem * m_base = nullptr;

};

#endif // INTERFACE_H
