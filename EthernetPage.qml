import QtQuick
import QtQuick.Controls
//import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    id: netPageRoot
    property real speed: 0.0

    // Heading
    RowLayout {
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Label {
            text: "Download"
            font.pointSize: 25
            font.bold: true
        }
    }

    Dial {
        id: dialComponent
        Layout.fillWidth: true
        Layout.minimumHeight: 350
        Layout.leftMargin: 15
        Layout.rightMargin: 15

        from: 0
        to: 100
        value: speed

        // Disable mouse input for dial
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
        }

        // Speed
        Label {
            anchors.centerIn: parent
            text: speed.toFixed(1) + " MB"
            font.pointSize: 25
            font.bold: true
        }
    }
}
