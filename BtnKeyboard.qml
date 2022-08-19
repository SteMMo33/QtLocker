import QtQuick 2.0

Item {
    id: button
    width: 120
    height: 120
    property alias keyName: keyName.text
    property alias textColor: keyName.color
    //property alias pressed: mouseArea.pressed
    //property alias pressedButtons: mouseArea.pressedButtons
    property alias mouse: mouseArea

    Rectangle {
        id: rectBackground
        radius: 20
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#e88705"
            }

            GradientStop {
                position: 1
                color: "#fed513"
            }
        }
        anchors.fill: parent

        Text {
            id: keyName
            text: qsTr("Text")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            styleColor: "#ffffff"
            style: Text.Sunken
            font.family: "Proxima Nova Rg"
            anchors.fill: parent
            font.pixelSize: 27
        }

        Rectangle {
            id: rectPressed
            opacity: 0.5
            visible: false
            color: "#848484"
            anchors.fill: parent
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onPressed: rectPressed.visible = true
            onReleased: rectPressed.visible = false
        }

    }

}


/*##^##
Designer {
    D{i:6}
}
##^##*/
