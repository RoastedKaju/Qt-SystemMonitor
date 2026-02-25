import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtCharts

ColumnLayout {
    id: control

    required property string processorName
    required property int processorUtil
    required property int logicalCores
    required property int physicalCores
    required property string processorArchitecture
    required property int l1Cache
    required property int l2Cache
    required property int l3Cache
    required property real clockSpeed;

    // Heading
    RowLayout {
        Layout.leftMargin: 10
        Layout.rightMargin:  10

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
        id: utilChart
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
            id: cpuLineSeries
            name: "CPU Usage"
            axisX: axisX
            axisY: axisY

            function refresh() {
                var data = ProcessorBackend.cpuUtilHistory
                cpuLineSeries.clear()
                for (var i = 0; i < data.length; i++)
                    cpuLineSeries.append(i, data[i])
            }

            Connections {
                target: ProcessorBackend
                function onCpuUtilHistoryChanged() { cpuLineSeries.refresh() }
            }

            Component.onCompleted: cpuLineSeries.refresh()
        }
    }

    // Information grid
    GridLayout {
        id: grid
        columns: 4

        columnSpacing: 50
        rowSpacing: 25

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

        // Physical cores Card
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Physical Cores"
            }

            Label {
                font.pointSize: 18
                text: physicalCores
            }
        }

        // Cache Sizes Card
        ColumnLayout {
            spacing: 5
            Label {
                font.pointSize: 8
                font.bold: true
                text: "Cache Sizes"
            }

            ColumnLayout {
                Label {
                    font.pointSize: 8
                    text: "L1 Cache: " + l1Cache + " KB"
                }
                Label {
                    font.pointSize: 8
                    text: "L2 Cache: "+ l2Cache + " MB"
                }
                Label {
                    font.pointSize: 8
                    text: "L3 Cache: " + l3Cache + " MB"
                }
            }
        }

        // Processor clock speed
        ColumnLayout {
            spacing: 0
            Label {
                font.pointSize: 8
                text: "Max Clock Speed"
            }

            Label {
                font.pointSize: 18
                text: clockSpeed.toPrecision(2) + " MHz"
            }
        }
    }
}
