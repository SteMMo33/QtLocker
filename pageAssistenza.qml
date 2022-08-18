import QtQuick 2.0
import QtQuick.Window 2.2



Window {
    id: pageAssistenza
    width: 1000
    height: 800

    visible: true
    // visibility: Window.FullScreen
    visibility: Qt.WindowFullScreen
    title: "Pagina assistenza"

    BtnKeyboard {
        id: btnKeyboard1
        x: 41
        y: 140
        width: 212
        height: 78
        keyName: "Cassetto 1"
        onPressedChanged: {
            console.log("PP")
            ioBoard.apriCassetto(1);
        }

    }

    BtnKeyboard {
        id: btnKeyboard2
        x: 41
        y: 224
        width: 212
        height: 90
        keyName: "Cassetto 2"
    }

    Text {
        id: element
        x: 185
        y: 23
        text: qsTr("ASSISTENZA") + " - Colonne: " + mysettings.get("numColumn")
        font.pixelSize: 46
        font.family: "Proxima Nova Rg"
        font.bold: true
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }

    BtnKeyboard {
        id: btnKeyboardReturn
        x: 80
        y: 506
        width: 624
        height: 68
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        keyName: "RITORNA ALLA PAGINA INIZIALE"
        onPressedChanged: {
            console.log("> Pressed ritorna")
            // parent.source = "qrc:/main.qml"
            Loader.source = ""
            pageAssistenza.close()
        }
    }

    BtnKeyboard {
        id: btnKeyboardApriTutti
        x: 446
        y: 140
        width: 309
        height: 78
        keyName: "Abilita tutti i cassetti"
        onPressedChanged: ioBoard.setInternalTable(40)
    }

    BtnKeyboard {
        id: btnKeyboardVite
        x: 446
        y: 224
        width: 309
        height: 78
        keyName: "Apri motore a vite"
        onPressedChanged: {
            console.log("> ", mysettings)
            for(var el in mysettings)
                console.log(": "+el)
            console.log("# "+mysettings.get("flag_esiste_pos"))
            console.log("# "+mysettings.get("posType"))
            console.log("# "+mysettings.get("posPort"))
        }
    }

    BtnKeyboard {
        id: btnKeyboardC22
        x: 41
        y: 320
        width: 212
        height: 90
        keyName: "Cassetto 22"
        onPressedChanged: ioBoard.apriCassetto(33)
    }


    Rectangle {
        id: rectangle
        x: 337
        y: 325
        width: 500
        height: 228
        color: "#ffffff"
        radius: 5
        border.width: 2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 130

        Text {
            id: element1
            color: "#ff0404"
            text: qsTr("Settings:")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.pixelSize: 19
            horizontalAlignment: Text.AlignLeft
            lineHeight: 1.2
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.topMargin: 5
            fontSizeMode: Text.VerticalFit
        }

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: element1.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            interactive: false
            model: mysettings.getObjMap()   /* ListModel {
            ListElement {
                name: "Grey"
                key: "key1"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                key: "Key2"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                key: "Key3"
                colorCode: "blue"
            }

        } */
            delegate: Item {
                x: 5
                width: 120
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: "#ffaaaa"
                    }

                    Text {
                        text: "Key"
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    Text {
                        text: "Val "+model.emailFarmacia
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }
        }
    }

}






