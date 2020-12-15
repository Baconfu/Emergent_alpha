import QtQuick 2.0

Rectangle{
    id: base
    objectName: "base"
    x:0
    y:0
    width:300
    height:101



    Item {
        id: info
        x: 0
        y: 0
        width: 300
        height: 80

        Text {
            id: chunk
            x: 205
            y: 30
            objectName: "current_chunk"
            property string chunk_coordinate: ""
            text: "chunk: " + chunk_coordinate
        }

        Text {
            id: tile
            x: 105
            y: 30
            objectName: "current_tile"
            property string tile_coordinates: ""
            text: "tile: " + tile_coordinates

        }

        Text {
            id: velocity
            x: 5
            y: 50
            height: 20
            objectName: "velocity"

            property string velocity: ""
            text: "v: " + velocity
        }

        Text {
            id: pos
            x: 5
            y:30

            objectName: "coordinate"

            property string coordinate: ""
            text: "pos: " + coordinate
        }

        Text {
            id: type_info
            objectName: "type"
            x: 5
            y: 5
            text: qsTr("Type: ")
            font.pixelSize: 12
        }



    }

    Item {
        id: proximal_display
        x: 0
        y: 80
        width: parent.width / 2
        height: 21 + proximal_list.height

        onHeightChanged: {
            if(height+80>parent.height){
                parent.height = 80 + height
            }
        }

        Text {
            id: proximal_header
            x: 5
            y: 0
            text: qsTr("Proximal Entities")
            font.pixelSize: 12
        }

        Column {
            id: proximal_list
            objectName: "proximal_list"
            x: 0
            y: 21
            width: parent.width

        }

    }

    Item {
        id: context_display
        x: parent.width/2
        y: 80
        width: parent.width/2
        height: 21 + context_list.height

        onHeightChanged: {
            if(height+80>parent.height){
                parent.height = 80 + height
            }
        }


        Column {
            id: context_list
            objectName: "context_list"
            x: 0
            y: 21
            width: parent.width
        }

        Text {
            id: context_header
            x: 5
            y: 0
            text: qsTr("Contexts")
            font.pixelSize: 12
        }
    }
}
