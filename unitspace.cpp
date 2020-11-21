#include "unitspace.h"
#include <math.h>

UnitSpace::UnitSpace(Coordinate c)
{
    pos = c;

}

void UnitSpace::assignObj(QQuickItem *obj)
{
    m_obj = obj;
    m_obj->setX(pos.x() * 30);
    m_obj->setY(pos.y() * 30 * sin(1.047));
}

