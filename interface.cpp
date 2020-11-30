#include "interface.h"

Interface::Interface(QQuickItem *parent):
    QQuickItem(parent)
{

}

void Interface::assignBase(QQuickItem *obj)
{
    m_base = obj;
    m_base->setParentItem(this);
    m_base->setPosition(QPointF(0,0));
    m_base->setWidth(width());
    m_base->setHeight(height());
}
