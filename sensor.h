#ifndef SENSOR_H
#define SENSOR_H

#include <entity.h>
#include <collidable.h>

class Sensor: public Collidable
{
public:
    Sensor();
    float reading() {return m_reading;}

private:
    float m_reading;
};

#endif // SENSOR_H
