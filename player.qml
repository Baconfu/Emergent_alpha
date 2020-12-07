import QtQuick 2.0
import Paint 1.0


PaintPlayer {
    x:0
    y:0


    width: 20
    height: 40
    m_anim: 0
    property int anim_cycle: 0
    onAnim_cycleChanged: {
        m_anim = anim_cycle
        update()
    }

}
