import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Emergent")

    signal keyPressed(int event_key)

    Keys.onPressed: {
        console.log("key_pressed")
        keyPressed(event.key)
    }
}
