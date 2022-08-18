import QtQuick 2.5
import QtQuick.Window 2.2
import com.amtek.locker 1.0


Rectangle {
    id: pnlPagamento
    visible: false
    color: "#000000"
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: pnlHeader.bottom
    anchors.bottom: parent.bottom
    
    
    Timer {
        property var fase: 0
        id: timerSimul
        running: false
        interval: 3000
        repeat: true
        onTriggered: {
            console.log("!timer "+fase)
            switch(fase){
            case 0:
                txtMsgPos.text = "Attendere la fine operazione .."
                fase = 1;
                break;
            case 1:
                txtMsgPos.text = "PAGATO CORRETTAMENTE - TODO"
                fase = 2;
                break;
            case 2:
                pnlPagamento.visible = false
                testo1.text = "Ritirare dal cassetto "+currentPrenotazione.cassetto
                testo2.text = "Prego .."
                pnlRitiroCassetto.visible = true
                // fallback
            default:
                fase = 0
                timerSimul.running = false
                console.log("Fine timer simul")
            }
        }
    }
    
    Rectangle {
        id: pnlPagamentoInterno
        width: 600
        visible: true
        color: "#00000000"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 40
        Text {
            id: txtValorePos
            height: 69
            visible: true
            color: "#f1ed02"
            text: qsTr("Importo da pagare")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 31
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.family: "Proxima Nova Rg"
            anchors.leftMargin: 0
            fontSizeMode: Text.VerticalFit
        }
        
        Text {
            id: txtMsgPos
            color: "#fed513"
            text: qsTr("MsgPos")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: txtValorePos.bottom
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            anchors.topMargin: 20
            font.bold: true
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }
        
        BtnLocker {
            id: btnPagaConPos
            width: 454
            height: 288
            anchors.top: txtMsgPos.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            textMain: "Paga con POS"
            textSec: "Clicca per pagare con il POS"
            anchors.topMargin: 50
            onClick: {
                console.log("Paga POS - TODO")
                timerSimul.running = true
            }
        }
        
        BtnLocker {
            id: btnPagaRitorna
            y: 527
            width: 720
            height: 73
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            textMain: "RITORNA ALLA PAGINA INIZIALE"
            textSec: ""
            onClick: showHome()
        }
        
        anchors.horizontalCenter: parent.horizontalCenter
        
        onVisibleChanged: {
            if (visible) txtMsgPos.text = ""
        }
    }
}
