#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
    Coordinate(int x =0 ,int y = 0,int z = 0);

    int x(){return m_x;}
    int y(){return m_y;}
    int z(){return m_z;}

    Coordinate operator+=(Coordinate &b){
        m_x += b.x();
        m_y += b.y();
        m_z += b.z();
        return *this;
    }


private:
    int m_x;
    int m_y;
    int m_z;

};

#endif // COORDINATE_H
