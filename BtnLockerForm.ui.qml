import QtQuick 2.5

Item {
    id: bottone
    width: 350
    height: 250

    property alias mouseArea: mouseArea
    property alias textMain: text1.text
    property alias textSec: text2.text
    property alias textMainSize: text1.font.pixelSize
    property alias textSecSize: text2.font.pixelSize

    FontLoader {
        id: proximaNovaBold
        source: "qrc:/fonts/ProximaNova-Bold.otf"
    }

    Rectangle {
        id: rectBackground
        width: 200
        height: 200
        radius: 18
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#9f8505"
            }

            GradientStop {
                position: 1
                color: "#fedb34"
            }
        }

        Text {
            id: text1
            y: bottone.height * 0.28
            height: 47
            color: "#fdfdfd"
            text: qsTr("Pri")
            anchors.left: parent.left
            anchors.right: parent.right
            style: Text.Sunken
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            font.family: "Proxima Nova Rg"
            anchors.rightMargin: 50
            anchors.leftMargin: 50
            font.bold: true
            fontSizeMode: Text.Fit
        }

        Text {
            id: text2
            y: bottone.height * 0.7
            height: 42
            color: "#fdfdfd"
            text: qsTr("Sec")
            anchors.left: parent.left
            anchors.right: parent.right
            wrapMode: Text.WordWrap
            font.family: "Proxima Nova Rg"
            anchors.rightMargin: 50
            anchors.leftMargin: 50
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
            fontSizeMode: Text.Fit
        }
    }

    Rectangle {
        id: rectOmbraPress
        visible: false
        color: "#80848484"
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: rectOmbraPress.visible = true
        onReleased: rectOmbraPress.visible = false
    }
}

/*##^##
Designer {
    D{i:0;height:250;width:350}D{i:8}
}
##^##*/


/*##^## Designer {
    D{i:7;anchors_height:100;anchors_width:100}
}
 ##^##*/

