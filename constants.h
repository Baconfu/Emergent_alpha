#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QStringLiteral>

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


    static const int hex_radius_units = 500;
};

#endif // CONSTANTS_H
