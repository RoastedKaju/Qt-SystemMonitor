import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.topMargin: 25
            spacing: 10
            Button { text: "Click me!" }
            Button { text: "Click me too!" }
        }

        Frame {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 400
            spacing: 10

            ColumnLayout {
                anchors.horizontalCenter: parent.horizontalCenter

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: "I am a Label"
                    font.bold: true
                }

                Button {
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 50
                    text: "Option 1"
                    onClicked: monitorSystemInfo.onButtonClicked()
                }
                Button {
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 50
                    text: "Option 2"
                }
            }
        }

        Frame {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 400
            spacing: 10

            ColumnLayout {
                anchors.horizontalCenter: parent.horizontalCenter

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Stats"
                    font.bold: true
                }

                Text {
                    id: ram
                    text: monitorSystemInfo ? monitorSystemInfo.memoryInfo : "Loading..."
                    font.pixelSize: 18
                }

                Text {
                    id: cpu
                    text: monitorSystemInfo ? monitorSystemInfo.cpuInfo : "Loading..."
                    font.pixelSize: 18
                }
            }
        }

        Frame
        {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 400
            Layout.preferredHeight: 400
            spacing: 10

            ColumnLayout
            {
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter

                Label
                {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Charts"
                    font.bold: true
                }

                ChartView
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    antialiasing: true

                    LineSeries
                    {
                        XYPoint { x: 0; y: 0 }
                        XYPoint { x: 1.1; y: 2.1 }
                        XYPoint { x: 1.9; y: 3.3 }
                        XYPoint { x: 2.1; y: 2.1 }
                        XYPoint { x: 2.9; y: 4.9 }
                        XYPoint { x: 3.4; y: 3.0 }
                        XYPoint { x: 4.1; y: 3.3 }
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
