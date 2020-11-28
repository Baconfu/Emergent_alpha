import QtQuick 2.0
import Paint 1.0


PaintTerrain {
    x: 0
    y: 0
    onZChanged: {
        update()
    }

    width: 30
    height: 40.98


}
