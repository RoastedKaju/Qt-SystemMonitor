import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtCharts

ColumnLayout {
    id: processorPageRoot
    property int processorUtil: 99
    property string processorName: "Fectching Info"
    property int logicalCores: -1
    property string processorArchitecture: "x00"
    property int l1: -1
    property int l2: -1
    property int l3: -1
    property var lineChartHistory: [] // For line chart

    // Heading
    RowLayout {
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Label {
            text: "CPU"
            font.pointSize: 25
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            text: processorName
            font.pointSize: 10
        }
    }

    // Chart
    ChartView {
        antialiasing: true

        Layout.fillWidth: true
        Layout.minimumHeight: 250

        ValueAxis {
            id: axisX
            min: 0
            max: 60
            titleText: "Seconds"
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 100
            titleText: "CPU %"
        }

        LineSeries {
            id: cpuSeries
            name: "CPU Utilization"
            axisX: axisX
            axisY: axisY
        }

        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                lineChartHistory.push(processorUtil)
                if (lineChartHistory.length > 60)
                    lineChartHistory.shift()

                cpuSeries.clear()
                for (var i = 0; i < lineChartHistory.length; ++i) { cpuSeries.append(i, lineChartHistory[i]) }
            }
        }
   }

    // Infomation Grid
    GridLayout {
        id: grid
        columns: 3

        columnSpacing: 50

        Layout.leftMargin: 10
        Layout.rightMargin: 10

        // Utilization Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Utilization"
            }

            Label {
                font.pointSize: 18
                text: processorUtil + "%"
            }
        }

        // Architecture Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Architecture"
            }

            Label {
                font.pointSize: 18
                text: processorArchitecture
            }
        }

        // Logical cores Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Logical Cores"
            }

            Label {
                font.pointSize: 18
                text: logicalCores
            }
        }

        // Cache Sizes Card
        ColumnLayout {
            spacing: 5
            Label {
                font.pointSize: 8
                text: "Cache Sizes (Per Core)"
            }

            ColumnLayout {
                Label {
                    font.pointSize: 8
                    text: "L1 Cache: " + l1 + " KB"
                }
                Label {
                    font.pointSize: 8
                    text: "L2 Cache: " + l2 + " KB"
                }
                Label {
                    font.pointSize: 8
                    text: "L3 Cache: " + l3 + " KB"
                }
            }
        }
    }
}
