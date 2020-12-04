import QtQuick 2.0
import Paint 1.0


PaintLadder {
    x:0
    y:0
    z:0
    width:30
    height:30
    m_painted_rotation: 0

    onRotationChanged: {
        update()
        console.log("rotation changed")
    }



}
