import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

import Paint 1.0

ApplicationWindow {
    id: myWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Emergent")

    signal keyPressed(int event_key)
    signal keyReleased(int event_key)
    signal closingWindow();

    onClosing: {
        closingWindow();
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
