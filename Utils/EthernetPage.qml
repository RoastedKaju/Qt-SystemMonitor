import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import QtQuick.Controls.Basic.impl
import QtQuick.Templates as T
import QtQuick.Layouts

ColumnLayout {
    id: control

    required property int speed

    // Heading
    RowLayout {
        Layout.leftMargin: 10
        Layout.rightMargin: 10

        Label {
            text: "Ethernet"
            font.pointSize: 25
            font.bold: true
        }
    }

    // Divider
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 1
        Layout.margins: 5
        color: "white"
    }

    // Dial
    Dial {
        id: dialComponent
        Layout.fillWidth: true
        Layout.minimumHeight: 350
        Layout.leftMargin: 15
        Layout.rightMargin: 15
        Layout.topMargin: 15

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

        background: DialImpl {
            implicitWidth: 184
            implicitHeight: 184
            color: "#FFCC00"
            progress: dialComponent.position
            opacity: dialComponent.enabled ? 1 : 0.3
            startAngle: dialComponent.startAngle
            endAngle: dialComponent.endAngle
        }

        handle: ColorImage {
            x: dialComponent.background.x + dialComponent.background.width / 2 - width / 2
            y: dialComponent.background.y + dialComponent.background.height / 2 - height / 2
            width: 14
            height: 10
            defaultColor: "#353637"
            color: "#FFCC00"
            source: "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/dial-indicator.png"
            antialiasing: true
            opacity: dialComponent.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(dialComponent.background.width, dialComponent.background.height) * 0.4
                       + (dialComponent.handle ? dialComponent.handle.height / 2 : 0)
                },
                Rotation {
                    angle: dialComponent.angle
                    origin.x: dialComponent.handle ? dialComponent.handle.width / 2 : 0
                    origin.y: dialComponent.handle ? dialComponent.handle.height / 2 : 0
                }
            ]
        }
    }
}
