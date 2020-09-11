import QtQuick 2.0
import QtQuick.Window 2.2



Window {
    id: pageAssistenza
    width: 950
    height: 700

    visible: true
    visibility: Window.FullScreen
    title: "Pagina assistenza"

    BtnKeyboard {
        id: btnKeyboard
        x: 41
        y: 140
        width: 212
        height: 78
        keyName: "Cassetto 1"
    }

    BtnKeyboard {
        id: btnKeyboard1
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
        id: btnKeyboard2
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
        }
    }

    BtnKeyboard {
        id: btnKeyboard3
        x: 446
        y: 140
        width: 309
        height: 78
        keyName: "Abilita tutti i cassetti"
        onPressedChanged: ioBoard.setInternalTable(40)
    }

    BtnKeyboard {
        id: btnKeyboard4
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

    ListView {
        id: listView
        x: 446
        y: 381
        width: 405
        height: 160
        model: mysettings/* ListModel {
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

            ListElement {
                name: "Green"
                colorCode: "green"
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
                    color: colorCode
                }

                Text {
                    text: "Key"
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                Text {
                    text: "N:"+name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                spacing: 10
            }
        }
    }


}




