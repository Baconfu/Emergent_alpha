import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Emergent")

    signal keyPressed(int event_key)
    signal keyReleased(int event_key)

    Item {
        id: root
        objectName: "root"
        focus: true
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
