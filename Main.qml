import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtCharts
import QtQuick.Shapes

import SystemMonitor
import "Utils"

Window {
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("System Monitor")

    Rectangle {
        anchors.fill: parent

        Shape {
            anchors.fill: parent

            ShapePath {
                strokeWidth: 0

                fillGradient: LinearGradient {
                    x1: 0; y1: 0
                    x2: width; y2: height

                    GradientStop { position: 0.0; color: "#222831" }
                    GradientStop { position: 0.5; color: "#222831" }
                    GradientStop { position: 1.0; color: "#FFE52A" }
                }

                startX: 0; startY: 0
                PathLine { x: width; y: 0 }
                PathLine { x: width; y: height }
                PathLine { x: 0; y: height }
                PathLine { x: 0; y: 0 }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 25
        radius: 10
        color: "#393E46"

        ColumnLayout {
            anchors.fill: parent

            Label {
                leftPadding: 8
                topPadding: 3
                bottomPadding: 3
                text: "Performance"
                font.pointSize: 11
                font.bold: true
                color: "white"
            }

            // Divider
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "grey"
            }

            // Row
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    Layout.fillHeight: true
                    Layout.minimumWidth: 150
                    Layout.leftMargin: 8
                    Layout.bottomMargin: 3
                    radius: 10
                    color: "#808080"

                    // Sidebar
                    ColumnLayout {
                        anchors.horizontalCenter: parent.horizontalCenter
                        ButtonGroup {
                            id: sidebarGroup
                            exclusive: true
                        }

                        SidebarButton {
                            Layout.topMargin: 15
                            text: "CPU"
                            checkable: true
                            checked: true            // default selected
                            ButtonGroup.group: sidebarGroup
                            onClicked: {
                                widgetStack.replace(cpuWidget)
                            }
                        }
                        SidebarButton {
                            text: "Memory"
                            checkable: true
                            ButtonGroup.group: sidebarGroup
                            onClicked: {
                                widgetStack.replace(memoryWidget)
                            }
                        }
                        SidebarButton {
                            text: "GPU"
                            checkable: true
                            ButtonGroup.group: sidebarGroup
                            onClicked: {
                                widgetStack.replace(gpuWidget)
                            }
                        }
                        SidebarButton {
                            text: "Ethernet"
                            checkable: true
                            ButtonGroup.group: sidebarGroup
                            onClicked: {
                                widgetStack.replace(ethernetWidget)
                            }
                        }
                    }
                }
                // Information area
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.rightMargin: 8
                    Layout.bottomMargin: 3
                    radius: 10
                    color: "#808080"

                    StackView {
                        id: widgetStack
                        anchors.top:  parent.top
                        width: parent.width
                        initialItem: cpuWidget
                        replaceEnter: null
                        replaceExit: null
                    }

                    Component {
                        id: cpuWidget
                        ProcessorPage {
                            processorName: ProcessorBackend.processorName
                            processorUtil: ProcessorBackend.cpuUtilHistory[59]
                            processorArchitecture: ProcessorBackend.architecture
                            logicalCores: ProcessorBackend.logicalCores
                            physicalCores: ProcessorBackend.physicalCores
                            l1Cache: ProcessorBackend.cacheSizes[0]
                            l2Cache: ProcessorBackend.cacheSizes[1]
                            l3Cache: ProcessorBackend.cacheSizes[2]
                            clockSpeed: ProcessorBackend.clockSpeed;
                        }
                    }
                    Component {
                        id: memoryWidget
                        MemoryPage {
                            totalMemory: MemoryBackend.totalMemory
                            usedMemory: MemoryBackend.usedMemory
                            freeMemory: MemoryBackend.freeMemory
                            vendorInfoList: MemoryBackend.vendorInfo
                        }
                    }
                    Component {
                        id: gpuWidget
                        GPUPage {
                            name: GPUBackend.gpuName
                            vendor: GPUBackend.vendorName
                            version: GPUBackend.driverVersion
                            memory: GPUBackend.memory
                        }
                    }
                    Component {
                        id: ethernetWidget
                        EthernetPage {
                            speed: EthernetBackend.downloadSpeed
                        }
                    }
                }
            }
        }
    }
}
