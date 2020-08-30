import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window
    width: 950
    height: 650
    visible: true
    property alias edtCodicePrenotazione: edtCodicePrenotazione
    title: qsTr("QtLocker")

    FontLoader { id: proximaNovaBold; source: "fonts/ProximaNova-Bold.otf" }
    FontLoader { id: proximaNovaRegular; source: "fonts/ProximaNova-Regular.otf" }

    Item {
        id: pnlHeader
        y: 0
        height: 150
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            id: rectHeaderBackg
            color: "#b1a7a7"
            radius: 18
            anchors.fill: parent

            Rectangle {
                id: rectHeaderLeft
                width: 200
                color: "#241b1b"
                radius: 15
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                anchors.leftMargin: 20
            }

            Rectangle {
                id: rectHeaderCenter
                color: "#241b1b"
                radius: 15
                anchors.left: rectHeaderLeft.right
                anchors.right: rectHeaderRight.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.rightMargin: 20
                anchors.leftMargin: 20
                anchors.bottomMargin: 10
                anchors.topMargin: 10

                Text {
                    id: txtHeaderC1
                    color: "#fdfdfd"
                    text: qsTr("Locker 1 - AMtek - Prova")
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    font.pixelSize: 21
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.HorizontalFit
                    font.bold: true
                    anchors.topMargin: 30
                    anchors.rightMargin: 15
                    anchors.leftMargin: 15
                }

                Text {
                    id: txtHeaderC2
                    y: 43
                    color: "#e88705"
                    text: qsTr("SELEZIONA IL SERVIZIO")
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    font.pixelSize: 19
                    horizontalAlignment: Text.AlignHCenter
                    anchors.bottomMargin: 20
                    font.bold: true
                    anchors.rightMargin: 30
                    anchors.leftMargin: 30
                }
            }

            Rectangle {
                id: rectHeaderRight
                x: 554
                width: 200
                color: "#241b1b"
                radius: 15
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.rightMargin: 20
                anchors.bottomMargin: 10
                anchors.topMargin: 10

                BtnLocker {
                    id: btnLockerDeposito
                    anchors.fill: parent
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    textSec: "Clicca per il deposito"
                    text1Main: "DEPOSITO ARTICOLO"
                    onClick: function(){
                        pnlDeposito.visible=true
                        pnlHome.visible=false
                    }
                }
            }
        }

    }

    Item {
        id: pnlHome
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        BtnLocker {
            id: btnLockerRitiroArticolo
            x: 14
            y: 25
            width: 381
            height: 266
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            textSec:  "Clicca qui per ritirare un articolo"
            text1Main: "RITIRO ARTICOLO"
            onClick: function(){
                pnlRitiro.visible = true
                pnlHome.visible = false
            }

        }
    }



    Item {
        id: pnlDeposito
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        Rectangle {
            id: pnlDepositoInterno
            width: 470
            color: "#ffffff"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            visible: true
            z: -8


            Text {
                id: element
                height: 69
                text: qsTr("Scritta in questa pagina")
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                fontSizeMode: Text.VerticalFit
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                visible: true
                font.pixelSize: 12
            }

            BtnLocker {
                id: btnLockerForm
                width: 254
                height: 190
                textSec: "SecForm"
                text1Main: "PriForm"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: element.bottom
                anchors.topMargin: 10
                onClick: function(){

                    console.log("TYTY")
                    pnlDeposito.visible = false;
                    pnlHome.visible = true;
                }

            }

        }
    }




    Item {
        id: pnlRitiro
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom


        Item {
            id: pnlRitiroInterna
            anchors.fill: parent
            anchors.rightMargin: 100
            anchors.leftMargin: 100



            Text {
                id: lblInserisci
                x: -100
                y: 40
                text: qsTr("Inserisci codice di prenotazione")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 23
                horizontalAlignment: Text.AlignHCenter
                anchors.topMargin: 40
                anchors.leftMargin: 0
                anchors.rightMargin: 0
            }




            Rectangle {
                id: pnlEditCodice
                width: 350
                height: 56
                color: "#ffffff"
                radius: 10
                border.width: 3
                anchors.top: lblInserisci.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter



                TextEdit {
                    id: edtCodicePrenotazione
                    text: qsTr("Codice prenotazione")
                    anchors.fill: parent
                    font.pixelSize: 26
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    font.bold: true
                    onFocusChanged: function(){
                        text=""
                        gridKeyboard.visible = focus
                    }
                    onActiveFocusChanged: console.log("onActFocCh");
                    onActiveFocusOnPressChanged: console.log("onActFocChOnPress");

                }


            }



            Item {
                id: pnlIstruzioni
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: pnlEditCodice.bottom
                anchors.bottom: parent.bottom
                anchors.topMargin: 10

                Image {
                    id: image
                    y: 68
                    width: 200
                    height: 200
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    source: "images/qr_code.png"
                    sourceSize.height: 350
                    sourceSize.width: 350
                    anchors.leftMargin: 120
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    id: lblIstruzioni
                    x: 0
                    y: 88
                    text: "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Tutte le scritte per la spiegazione ed istruzioni.</p>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Istruzioni per il ritiro</span></p>\n<ol style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" font-size:10pt; font-weight:600;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Scansionare il codice a barre</li>\n<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Passo 2</li>\n<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Passo 3</li></ol>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">In caso di difficoltà fare in altro modo</p></body></html>"
                    anchors.left: image.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    font.pixelSize: 17
                    textFormat: Text.RichText
                    anchors.bottomMargin: 50
                    fontSizeMode: Text.Fit
                    anchors.topMargin: 30
                    anchors.leftMargin: 30
                    anchors.rightMargin: 30
                }

            }

            Grid {
                id: gridKeyboard
                width: 450
                height: 250
                spacing: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                rows: 4
                columns: 3
                anchors.horizontalCenter: parent.horizontalCenter
                visible: false

                BtnKeyboard {
                    id: btnKey1
                    keyName: "1"
                    onPressedChanged: function(){
                        if(pressedButtons) edtCodicePrenotazione.text += "1"
                    }
                }

                BtnKeyboard {
                    id: btnKey2
                    width: 100
                    height: 100
                    keyName: "2"
                    onPressedChanged: if(pressedButtons) edtCodicePrenotazione.text += "2"
                }

                BtnKeyboard {
                    id: btnKey3
                    keyName: "3"
                    onPressedChanged: if(pressedButtons) edtCodicePrenotazione.text += "3"
                }

                BtnKeyboard {
                    id: btnKey4
                    keyName: "4"
                    onPressedChanged: if(pressedButtons) edtCodicePrenotazione.text += "4"
                }

                BtnKeyboard {
                    id: btnKey5
                    keyName: "5"
                }

                BtnKeyboard {
                    id: btnKbdHide
                    keyName: "Hide"
                    onPressedChanged: function(){
                        pnlRitiro.visible=false
                        pnlHome.visible = true
                        gridKeyboard.visible = false
                    }
                }


            }





        }
    }





}

/*##^##
Designer {
    D{i:3}D{i:5}D{i:6}D{i:4}D{i:8}D{i:7}D{i:2}D{i:1}D{i:14;invisible:true}D{i:15;invisible:true}
D{i:9;invisible:true}D{i:17;invisible:true}D{i:22}D{i:24}D{i:25}D{i:23}D{i:26}D{i:19}
}
##^##*/

























































/*##^## Designer {
    D{i:9;invisible:true}D{i:14;anchors_height:200}
}
 ##^##*/
