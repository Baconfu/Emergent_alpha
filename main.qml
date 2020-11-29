import QtQuick 2.15
import QtQuick.Window 2.15

import Paint 1.0

Window {
    id: myWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Emergent")

    signal keyPressed(int event_key)
    signal keyReleased(int event_key)

    Item {
        id: winBase
        objectName: "winBase"
        Item {
            id: root
            objectName: "root"
            focus: true

            transform: Scale {
                origin.x: myWin.width/2
                origin.y: myWin.height/2
                xScale:1
                yScale:1.153
            }

            x:0
            y:0
            width: myWin.width
            height: myWin.height

            PaintGrid {
                x:0
                y:0
                width: 6000
                height: 6000
            }

            Keys.onPressed: {
                if(!event.isAutoRepeat){
                    keyPressed(event.key)
                }
            }
            Keys.onReleased: {
                if(!event.isAutoRepeat){
                    keyReleased(event.key)
                }
            }
        }
    }




}
