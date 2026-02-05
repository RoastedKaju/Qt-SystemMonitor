import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    id: memoryPageRoot
    property int totalRamGb: 99
    property real inUseRamGb: 99.9
    property real comittedGb: 99.9
    property int loadPercent: 99
    property string pageFileString: "00 / 99"

    // Heading
    RowLayout {
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Label {
            text: "Memory"
            font.pointSize: 25
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            text: totalRamGb + " GB"
            font.pointSize: 10
        }
    }

    // Memory Bar
    ProgressBar {
        id: bar
        Layout.fillWidth: true
        Layout.minimumHeight: 50
        Layout.leftMargin: 15
        Layout.rightMargin: 15

        from: 0
        to: 100
        value: loadPercent
    }

    // Memory bar labels
    RowLayout {
        Layout.fillWidth: true
        Layout.leftMargin: 15
        Layout.rightMargin: 15

        Label { text: "0%" }
        Item { Layout.fillWidth: true }
        Label { text: "100%" }
    }

    // Grid Info
    GridLayout {
        id: grid
        columns: 3

        columnSpacing: 50

        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Layout.topMargin: 15

        // Used memory Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "In Use"
            }

            Label {
                font.pointSize: 18
                text: inUseRamGb + " GB"
            }
        }

        // Used memory Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Comitted"
            }

            Label {
                font.pointSize: 18
                text: comittedGb.toFixed(2) + " GB"
            }
        }

        // Page File Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Page File"
            }

            Label {
                font.pointSize: 18
                text: pageFileString + " GB"
            }
        }

        // Load Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Load"
            }

            Label {
                font.pointSize: 18
                text: loadPercent + "%"
            }
        }
    }
}
