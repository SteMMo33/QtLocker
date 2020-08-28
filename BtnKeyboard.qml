import QtQuick 2.0

Item {
    id: element
    width: 120
    height: 120
    property alias keyName: keyName.text
    property alias pressed: mouseArea.pressed
    property alias pressedButtons: mouseArea.pressedButtons

    Rectangle {
        id: rectBackground
        radius: 20
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#00ff00"
            }

            GradientStop {
                position: 1
                color: "#006600"
            }
        }
        anchors.fill: parent

        Text {
            id: keyName
            text: qsTr("Text")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            font.pixelSize: 27
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

}
