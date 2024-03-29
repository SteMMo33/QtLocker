import QtQuick 2.5
import QtQuick.Window 2.2
import com.amtek.locker 1.0


Window {

    id: mainWindow
    visible: true
    visibility: Qt.WindowFullScreen
    color: "black"
    title: qsTr("QtLocker")


    property alias edtCodicePrenotazione: edtCodicePrenotazione

    property var currentPrenotazione
    property var tipoOperazione

    FontLoader { id: proximaNovaBold; source: "fonts/ProximaNova-Bold.otf" }
    FontLoader { id: proximaNovaRegular; source: "fonts/ProximaNova-Regular.otf" }

    Component.onCompleted: showHome()   // Script iniziale

    function showHome(){
        pnlDeposito.visible = false
        pnlRitiro.visible = false
        pnlPagamento.visible = false
        btnLockerDeposito.visible = true
        pnlOperazioneCassetto.visible = false

        txtHeaderC2.text = "SELEZIONA IL SERVIZIO"
        pnlHome.visible = true
    }

    Loader {
        id: ld
    }

    Rectangle {

        id: pnlState
        anchors.fill: parent

    Rectangle {
        id: pnlHeader
        y: 0
        height: 150
        color: "black"
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
                color: "#868f96"
                radius: 15
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#868f96"
                    }

                    GradientStop {
                        position: 1
                        color: "#596164"
                    }
                }
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                anchors.leftMargin: 20

                // property variant win;

                Image {
                    id: image1
                    anchors.fill: parent
                    source: "images/logo-amtek.png"
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 20
                    anchors.topMargin: 20
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    id: mouseArea
                    x: 10
                    y: 20
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        console.log("Open pageAssistenza")
                        ld.source = "pageAssistenza.qml"
                    }
                }

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
                    height: 37
                    color: "#fdfdfd"
                    text: farmacia_name
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    font.pixelSize: 35
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Proxima Nova Rg"
                    fontSizeMode: Text.Fit
                    font.bold: true
                    anchors.topMargin: 30
                    anchors.rightMargin: 15
                    anchors.leftMargin: 15
                }

                Text {
                    id: txtHeaderC2
                    y: 87
                    height: 23
                    color: "#e88705"
                    text: qsTr("SELEZIONA IL SERVIZIO")
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    font.pixelSize: 23
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.Fit
                    font.family: "Proxima Nova Rg"
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
                color: "#868f96"
                radius: 15
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#868f96"
                    }

                    GradientStop {
                        position: 1
                        color: "#596164"
                    }
                }
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
                    textSecSize: 11
                    textSec: "Clicca per fare un deposito"
                    textMain: "DEPOSITO ARTICOLO"
                    onClick: function(){
                        console.log("> Click deposito")
                        // pnlDeposito.visible=true
                        pnlHome.visible=false

                        tipoOperazione = "deposito"
                        pnlRitiro.visible = true
                        txtHeaderC2.text = "DEPOSITO ARTICOLO"
                    }
                }
            }
        }

    }

    Rectangle {
        id: pnlHome
        color: "#000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        BtnLocker {
            id: btnLockerRitiroArticolo
            x: 14
            width: 589
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 150
            anchors.top: parent.top
            anchors.topMargin: 150
            anchors.horizontalCenter: parent.horizontalCenter
            textSecSize: 23
            textMainSize: 48
            textSec:  "Clicca qui per ritirare un articolo"
            textMain: "RITIRO ARTICOLO"
            onClick: function(){
                tipoOperazione = 'ritiro'
                pnlRitiro.visible = true
                pnlHome.visible = false
                btnLockerDeposito.visible = false

                txtHeaderC2.text = "RITIRO ARTICOLO"
            }

        }

        Image {
            id: image2
            x: 213
            y: 163
            width: 100
            height: 100
            source: "images/logo-amtek.png"
            scale: 5
            rotation: -11
            z: 0
            fillMode: Image.PreserveAspectFit
        }
    }



    Rectangle {
        id: pnlDeposito
        visible: true
        color: "#000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        Rectangle {
            id: pnlDepositoInterno
            width: 520
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            visible: true
            color: "#00000000"
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
                width: 454
                height: 72
                textSec: ""
                textMain: "RITORNA ALLA PAGINA"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: element.bottom
                anchors.topMargin: 10
                onClick: function(){
                    showHome()
                }
            }

            BtnLocker {
                id: btnLockerC1
                y: 172
                width: 235
                height: 76
                anchors.left: parent.left
                anchors.leftMargin: 0
                textMain: "Cassetto 1"
                textSec: ""
                onClick: ioBoard.apriCassetto(1)
            }

            BtnLocker {
                id: btnLockerC2
                y: 264
                width: 235
                height: 76
                anchors.left: parent.left
                textMain: "Cassetto 2"
                textSec: ""
                onClick: ioBoard.apriCassetto(2)
            }

            BtnLocker {
                id: btnLockerC21
                y: 355
                width: 235
                height: 76
                anchors.left: parent.left
                textSec: ""
                textMain: "Cassetto 21"
                onClick: ioBoard.apriCassetto(21)
            }

            BtnLocker {
                id: btnLockerC22
                y: 441
                width: 235
                height: 75
                anchors.left: parent.left
                textSec: ""
                textMain: "Cassetto 22"
                onClick: ioBoard.apriCassetto(22)
            }

            BtnLocker {
                id: btnLockerEmail
                x: 285
                y: 172
                width: 235
                height: 77
                anchors.right: parent.right
                anchors.rightMargin: 0
                textSec: ""
                textMain: "Email"
                onClick: {
                    console.log("> email")
                    prenotazioni.sendEmail()
                }
            }

            BtnLocker {
                id: btnLockerSetTable
                x: 285
                y: 264
                width: 235
                height: 77
                anchors.right: parent.right
                anchors.rightMargin: 0
                textSec: ""
                textMain: "Set int. table"
                onClick: ioBoard.setInternalTable(14)
            }

        }
    }





    Rectangle {
        id: pnlRitiro
        visible: true
        color: "#000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        onVisibleChanged: {
            console.log("- pnlRitiro visible:"+visible+ " - "+tipoOperazione)
            if (visible){
                txtMsg.text = ""
                edtCodicePrenotazione.text = ""
                edtCodicePrenotazione.focus = true

                if (tipoOperazione==='deposito')
                    lblInserisci.text = "Inserisci il codice di prenotazione"
                else
                    lblInserisci.text = "Inserisci il codice di ritiro"
            }
        }

        Item {
            id: pnlRitiroInterna
            anchors.fill: parent


            Text {
                id: lblInserisci
                x: -100
                y: 40
                color: "#fed513"
                text: qsTr("Inserisci il codice di prenotazione")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 23
                horizontalAlignment: Text.AlignHCenter
                font.family: "Proxima Nova Rg"
                anchors.topMargin: 40
                anchors.leftMargin: 0
                anchors.rightMargin: 0
            }


            Rectangle {
                id: pnlEditCodice
                width: 500
                height: 70
                color: "#ffffff"
                radius: 18
                border.color: "#848484"
                border.width: 7
                anchors.top: lblInserisci.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                TextInput {
                    id: edtCodicePrenotazione
                    visible: true
                    text: qsTr("Codice prenotazione")
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    font.pixelSize: 32
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    font.family: "Proxima Nova Rg"
                    font.bold: true

                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    selectByMouse: false

                    /* onFocusChanged: function(){
                        console.log("onFocusChanged")
                        text=""
                        pnlKeyboard.visible = focus
                    } */
                    /* onActiveFocusChanged: {

                        console.log("onActFocusChgd: "+focus);
                        pnlKeyboard.visible = focus
                    } */
                    onActiveFocusOnPressChanged: {
                        // gridKeyboard
                        console.log("onActFocusOnPressChgd: "+focus);
                    }

                    onAccepted: function(){
                        console.log("Code Accepted")
                        handleCode()
                    }

                }

                MouseArea {
                    id: mouseAreaEdit
                    anchors.fill: parent
                    onClicked: pnlKeyboard.visible = true
                }

            }


            Text {
                id: txtMsg
                height: 44
                color: "#ff0404"
                text: qsTr("Msg")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: pnlEditCodice.bottom
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                minimumPixelSize: 30
                anchors.topMargin: 18
                anchors.rightMargin: 100
                anchors.leftMargin: 100
                fontSizeMode: Text.Fit
                font.family: "Proxima Nova Rg"
            }

            Item {
                id: pnlIstruzioni
                width: 800
                anchors.top: pnlEditCodice.bottom
                anchors.bottom: btnBackHome.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 35



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
                    anchors.leftMargin: 50
                    fillMode: Image.PreserveAspectFit
                }




                Rectangle {
                    id: rectBackIstruzioni
                    width: 504
                    height: 350
                    color: "#848484"
                    radius: 18
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 35

                    Text {
                        id: lblIstruzioni
                        color: "#fdfdfd"
                        text: "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600;\">ISTRUZIONI PER IL RITIRO</span></p>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:18pt;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600;\">Istruzioni per il ritiro</span></p>\n<ol style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" font-size:18pt; font-weight:600;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">Scansionare il codice a barre</span></li>\n<li style=\" font-size:18pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Attendere l'apertura del cassetto</li>\n<li style=\" font-size:18pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Prelevare l'articolo e richiudere il cassetto</li>\n<li style=\" font-size:18pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Passo 4</li></ol>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px; font-size:18pt;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">In caso di difficoltà fare in altro modo</span></p></body></html>"
                        anchors.fill: parent
                        font.pixelSize: 40
                        wrapMode: Text.WordWrap
                        font.family: "Proxima Nova Rg"
                        anchors.rightMargin: 25
                        anchors.leftMargin: 25
                        anchors.bottomMargin: 30
                        anchors.topMargin: 30
                        textFormat: Text.RichText
                        fontSizeMode: Text.Fit
                    }
                }

            }


            Rectangle {
                id: pnlKeyboard
                width: 394
                height: 508
                visible: false
                color: "#ffaaaa"
                radius: 10
                anchors.top: pnlEditCodice.bottom
                anchors.topMargin: 60
                anchors.horizontalCenter: parent.horizontalCenter

                Grid {
                    id: gridKeyboard
                    x: 24
                    width: 364
                    opacity: 1
                    spacing: 2
                    rows: 4
                    columns: 3
                    visible: true
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    verticalItemAlignment: Grid.AlignVCenter
                    horizontalItemAlignment: Grid.AlignHCenter
                    clip: false

                    BtnKeyboard {
                        id: btnKey1
                        keyName: "1"
                        mouse.onClicked: function(){
                            edtCodicePrenotazione.text += "1"
                        }
                    }

                    BtnKeyboard {
                        id: btnKey2
                        keyName: "2"
                        mouse.onClicked: edtCodicePrenotazione.text += "2"
                    }

                    BtnKeyboard {
                        id: btnKey3
                        keyName: "3"
                        mouse.onClicked: edtCodicePrenotazione.text += "3"
                    }

                    BtnKeyboard {
                        id: btnKey4
                        keyName: "4"
                        mouse.onClicked: if(pressedButtons) edtCodicePrenotazione.text += "4"
                    }

                    BtnKeyboard {
                        id: btnKey5
                        keyName: "5"
                        mouse.onClicked: edtCodicePrenotazione.text += "5"
                    }

                    BtnKeyboard {
                        id: btnKey6
                        keyName: "6"
                        mouse.onClicked: edtCodicePrenotazione.text += "6"
                    }

                    BtnKeyboard {
                        id: btnKey7
                        keyName: "7"
                        mouse.onClicked: edtCodicePrenotazione.text += "7"
                    }

                    BtnKeyboard {
                        id: btnKey8
                        keyName: "8"
                        mouse.onClicked: edtCodicePrenotazione.text += "8"
                    }

                    BtnKeyboard {
                        id: btnKey9
                        keyName: "9"
                        mouse.onClicked: edtCodicePrenotazione.text += "9"
                    }

                    BtnKeyboard {
                        id: btnKbdCanc
                        textColor: "#ff0404"
                        keyName: "CANC"
                        mouse.onClicked: function(){
                            if (pressedButtons){
                                // showHome()
                                // edtCodicePrenotazione.text = edtCodicePrenotazione.text.substring( 0, edtCodicePrenotazione.text.length)
                                edtCodicePrenotazione.text = edtCodicePrenotazione.text.slice( 0, -1)
                            }
                        }
                    }

                    BtnKeyboard {
                        id: btnKey0
                        keyName: "0"
                        mouse.onClicked: if(pressedButtons) edtCodicePrenotazione.text += "0"
                    }

                    BtnKeyboard {
                        id: btnKeyOk
                        textColor: "#2db502"
                        keyName: "OK"
                        mouse.onClicked: function(){
                            handleCode();
                        }
                    }

                }
            }


            BtnLocker {
                id: btnBackHome
                x: 0
                y: 557
                width: 714
                height: 78
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 15
                textMain: "TORNA ALLA PAGINA INIZIALE"
                textSec: ""
                onClick: showHome()
            }

        }
    }

    Prenotazione {
        id: prenotazioneCheck
        // onCassettoChanged: function(x) { console.log("! cassChanged ", x)}
        // onImportoChanged: function(x) { console.log("! importoChanged ", x)}
    }

    PnlPagamento {
        id: pnlPagamento
    }



    Rectangle {
        id: pnlOperazioneCassetto
        visible: true
        color: "#000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pnlHeader.bottom
        anchors.bottom: parent.bottom

        onVisibleChanged: {
            console.log("pnlOperazioneCassetto "+visible)
            if (visible) timerRitiroCassetto.running = 1
        }

        Timer {
            id: timerRitiroCassetto
            interval: 6000;
            running: false;
            repeat: false
            onTriggered: showHome()
        }

        Text {
            id: testo1
            y: 138
            height: 58
            color: "#fed513"
            text: qsTr("Text")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.family: "Proxima Nova Rg"
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            fontSizeMode: Text.Fit
        }

        Text {
            id: testo2
            y: 231
            height: 54
            color: "#fed513"
            text: qsTr("Text2")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            font.family: "Proxima Nova Rg"
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }

        Text {
            id: testo3
            y: 329
            height: 37
            color: "#f7f7f7"
            text: qsTr("Text3")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.family: "Proxima Nova Rg"
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            fontSizeMode: Text.Fit
        }
    }


    Timer {
        id: timerEsito
        interval: 2000; running: false; repeat: false
        onTriggered: txtMsg.text = ""
    }


    states: [
        State {
            name: "Deposito"
            PropertyChanges {
                target: object

            }
        },
        State {
            name: "Ritiro"
            PropertyChanges {
                target: object

            }
        }
    ]


    }


    function showTimedMsg(text){
        txtMsg.text = text
        timerEsito.start()
    }


function handleCode()
{
    console.log("OK - "+edtCodicePrenotazione.text+" - tipoOperazione:"+tipoOperazione)

    if (edtCodicePrenotazione){
        pnlKeyboard.visible = false

        currentPrenotazione = ds.checkCode(
                    tipoOperazione==='deposito' ? TipoPrenotazione.TIPO_DEPOSITO : TipoPrenotazione.TIPO_RITIRO,
                    edtCodicePrenotazione.text)

        console.log("ret: "+currentPrenotazione)
        if (currentPrenotazione===null)
            showTimedMsg("Prenotazione non trovata")
        else {
            showTimedMsg("Prenotazione trovata !")

            console.log("id: "+currentPrenotazione.id)
            console.log("cass: "+currentPrenotazione.cassetto)
            console.log("imp: "+currentPrenotazione.importo)
            console.log("depo: "+currentPrenotazione.isDepositata)
            console.log("rit: "+currentPrenotazione.isRitirata)

            if(tipoOperazione==='deposito')
            {
                if (currentPrenotazione.isDepositata){
                    if (currentPrenotazione.isRitirata){
                        showTimedMsg("Prenotazione scaduta")
                        return
                    }
                    showTimedMsg("Prenotazione già depositata")
                    return
                }

                // Passo alla pagina di apertura cassetto
                testo1.text = "Depositare nel cassetto n. " + currentPrenotazione.cassetto
                testo2.text = "Depositare " + currentPrenotazione.cassetto
                testo3.text = "Dopo il deposito per cortesia chiudere il cassetto"
                pnlOperazioneCassetto.visible = true

                ioBoard.apriCassetto(currentPrenotazione.cassetto)
            }
            else { // Ritiro !

            if (!currentPrenotazione.isDepositata){
                showTimedMsg("Prenotazione non depositata")
                return
            }

            if (currentPrenotazione.isRitirata){
                showTimedMsg("Prenotazione già ritirata")
                return
            }

            pnlRitiro.visible = false

            if (currentPrenotazione.importo){
                txtValorePos.text = "E' richiesto il pagamento di € " + currentPrenotazione.importo.toFixed(2)
                pnlPagamento.visible = true
            }
            else {
                testo1.text = "Prelevare dal cassetto n. " + currentPrenotazione.cassetto
                testo2.text = "Prelevare dal cassetto n. " + currentPrenotazione.cassetto
                testo3.text = "Dopo il ritiro per cortesia chiudere il cassetto"
                pnlOperazioneCassetto.visible = true

                ioBoard.apriCassetto(currentPrenotazione.cassetto)
            }
        }
        }
    }
}

}


/*##^##
Designer {
    D{i:0;autoSize:true;height:700;width:900}D{i:21;invisible:true}D{i:24;invisible:true}
D{i:34;invisible:true}D{i:62;invisible:true}
}
##^##*/
