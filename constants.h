#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QStringLiteral>
#include <QVector3D>

class Constants
{
public:
    Constants();

    static const int tile_width_pixels = 30;
    static const int chunk_width_tiles = 20;
    static const int player_width_pixels = 20;
    static const int player_height_pixels = 40;
    static const int world_width_chunks = 3;
    static const int chunk_layer_count_tiles = chunk_width_tiles*chunk_width_tiles;
    static const int tick_duration = 18;
    static const int gravity_per_second = 10;
    static const int hex_radius_units = 500;

    static QVector3D getIntegerVector(QVector3D v){return QVector3D(int(v.x()),int(v.y()),int(v.z()));}

};

#endif // CONSTANTS_H
