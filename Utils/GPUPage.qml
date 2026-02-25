import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    id: control

    required property string name
    required property string vendor
    required property string version
    required property real memory

    // Heading
    Label {
        Layout.leftMargin: 10
        Layout.alignment: Qt.AlignLeft

        text: "GPU"
        font.pointSize: 25
        font.bold: true
    }

    // Divider
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 1
        Layout.margins: 5
        color: "white"
    }

    // Information grid
    GridLayout {
        id: grid
        columns: 1

        columnSpacing: 50
        rowSpacing: 25

        Layout.leftMargin: 10
        Layout.rightMargin: 10

        // Name card
        ColumnLayout {
            Label {
                text: "Card"
                font.pointSize: 8
                font.bold: true
            }
            Label {
                text: name
                font.pointSize: 18
                font.bold: true
            }
            // Divider
            Rectangle {
                Layout.preferredWidth: 350
                Layout.preferredHeight: 1
                color: "white"
            }
        }

        // Vendor
        ColumnLayout {
            Label {
                text: "Vendor"
                font.pointSize: 8
                font.bold: true
            }
            Label {
                text: vendor
                font.pointSize: 18
                font.bold: true
            }
            // Divider
            Rectangle {
                Layout.preferredWidth: 350
                Layout.preferredHeight: 1
                color: "white"
            }
        }

        // Version
        ColumnLayout {
            Label {
                text: "Version"
                font.pointSize: 8
                font.bold: true
            }
            Label {
                text: version
                font.pointSize: 18
                font.bold: true
            }
            // Divider
            Rectangle {
                Layout.preferredWidth: 350
                Layout.preferredHeight: 1
                color: "white"
            }
        }

        // Dedicated Memory
        ColumnLayout {
            Label {
                text: "Memory"
                font.pointSize: 8
                font.bold: true
            }
            Label {
                text: memory.toPrecision(2) + " GB"
                font.pointSize: 18
                font.bold: true
            }
            // Divider
            Rectangle {
                Layout.preferredWidth: 350
                Layout.preferredHeight: 1
                color: "white"
            }
        }
    }
}
