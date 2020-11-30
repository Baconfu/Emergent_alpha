import QtQuick 2.0
import Paint 1.0


PaintLadder {
    x:0
    y:0
    z:0
    width:30
    height:14
    m_rotation: 0

    onM_rotationChanged: {
        update()
    }

    Component.onCompleted: {
        update()
        console.log("complete")
    }


}
