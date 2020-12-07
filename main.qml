import QtQuick 2.12
import QtQuick.Window 2.12

import Paint 1.0

Window {
    id: myWin
    visible: true
    width: 1000
    height: 480
    title: qsTr("Emergent")

    signal keyPressed(int event_key)
    signal keyReleased(int event_key)
    signal mouseHover(int x,int y)
    signal mousePressed()

    Item {
        id: info_panel
        objectName: "info_panel"
        x: 640
        y: 0
        z:1
        width: myWin.width - x
        height: myWin.height

        Rectangle {
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            z:-1
            border.color: "grey"
            border.width: 1
            color: "white"

        }
    }



    Item {
        id: root
        objectName: "root"
        focus: true

        transform: Scale{
            yScale:1.153
        }

        x:0
        y:0
        width: 640
        height: myWin.height
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onMouseXChanged: {
                myWin.mouseHover(mouseX,mouseY)
            }
            onMouseYChanged: {
                myWin.mouseHover(mouseX,mouseY)
            }
            onClicked: {
                myWin.mousePressed()
            }
            focus: true
        }

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
