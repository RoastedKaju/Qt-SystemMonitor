import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls.impl
import QtQuick.Controls.Fusion
import QtQuick.Controls.Fusion.impl
import QtQuick.Layouts

ColumnLayout {
    id: control

    required property real totalMemory
    required property real usedMemory
    required property real freeMemory
    required property var vendorInfoList

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
            text: totalMemory.toPrecision(2) + " GB"
            font.pointSize: 10
        }
    }

    // Divider
    Rectangle {
        Layout.preferredHeight: 1
        Layout.fillWidth: true
        Layout.margins: 5
        color: "white"
    }

    // Memory Bar
    ProgressBar {
        id: bar
        Layout.fillWidth: true
        Layout.minimumHeight: 50
        Layout.leftMargin: 15
        Layout.rightMargin: 15

        from: 0
        to: 1
        value: usedMemory / totalMemory

        // Copied from Fusion
        contentItem: Item {
            implicitWidth: 120
            implicitHeight: 24
            scale: control.mirrored ? -1 : 1

            Rectangle {
                height: parent.height
                width: (bar.indeterminate ? 1.0 : bar.position) * parent.width

                radius: 2
                border.color: Qt.darker("#EB5B00", 1.4)
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#FF8C42"
                    }
                    GradientStop {
                        position: 1
                        color: "#EB5B00"
                    }
                }
            }

            Item {
                x: 1; y: 1
                width: parent.width - 2
                height: parent.height - 2
                visible: bar.indeterminate
                clip: true

                ColorImage {
                    width: Math.ceil(parent.width / implicitWidth + 1) * implicitWidth
                    height: parent.height

                    mirror: bar.mirrored
                    fillMode: Image.TileHorizontally
                    source: "qrc:/qt-project.org/imports/QtQuick/Controls/Fusion/images/progressmask.png"
                    color: Color.transparent(Qt.lighter(Fusion.highlight(bar.palette), 1.2), 160 / 255)

                    visible: bar.indeterminate
                    NumberAnimation on x {
                        running: bar.indeterminate && bar.visible
                        from: -31 // progressmask.png width
                        to: 0
                        loops: Animation.Infinite
                        duration: 750
                    }
                }
            }
        }
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
        rowSpacing: 25

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
                text: usedMemory.toPrecision(2) + " GB"
            }
        }

        // Used memory Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Free"
            }

            Label {
                font.pointSize: 18
                text: freeMemory.toPrecision(2) + " GB"
            }
        }
    }

    // Divider
    Rectangle {
        Layout.preferredHeight: 1
        Layout.fillWidth: true
        Layout.margins: 5
        color: "white"
    }

    // Vendor information
    ColumnLayout {
        id: vendorInfo
        Layout.leftMargin: 10
        Layout.rightMargin: 10

        Repeater {
            model: vendorInfoList
            delegate: ColumnLayout {
                spacing: 2
                Label { text: "Vendor: " + modelData.vendor }
                Label { text: "Name: " + modelData.name }
                Label { text: "Size: " + modelData.total_Bytes + " GB"}
                Rectangle {
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 1
                    color: "white"
                }
            }
        }
    }
}
