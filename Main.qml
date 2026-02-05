import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtCharts

import SystemMonitor

Window {
    width: 800
    height: 600
    minimumHeight: 600
    minimumWidth: 800
    visible: true
    title: qsTr("System Info")

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "#222831" }
            GradientStop { position: 0.5; color: "#222831" }
            GradientStop { position: 1.0; color: "#FFE52A" }
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
                        SidebarButton {
                            Layout.topMargin: 15
                            text: "CPU"
                            onClicked: {
                                widgetStack.replace(cpuComponent)
                            }
                        }
                        SidebarButton {
                            text: "Memory"
                            onClicked: {
                                widgetStack.replace(memoryComponent)
                            }
                        }
                        SidebarButton {
                            text: "Ethernet"
                            onClicked: {
                                widgetStack.replace(netComponent)
                            }
                        }
                        SidebarButton {
                            text: "GPU"
                            onClicked: {
                                widgetStack.replace(gpuComponent)
                            }
                        }
                    }
                }

                // Graph Area
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.rightMargin: 8
                    Layout.bottomMargin: 3
                    radius: 10
                    color: "#808080"

                    StackView {
                        id: widgetStack
                        anchors.top: parent.top
                        width: parent.width
                        initialItem: cpuComponent
                        replaceEnter: null
                        replaceExit: null
                    }

                    Component {
                        id: cpuComponent
                        ProcessorPage {
                            processorUtil: SystemInfo.cpuUtil
                            processorName: SystemInfo.cpuName
                            logicalCores: SystemInfo.logicalCores
                            processorArchitecture: SystemInfo.architecture
                            l1: SystemInfo.cacheSizeL1
                            l2: SystemInfo.cacheSizeL2
                            l3: SystemInfo.cacheSizeL3
                        }
                    }

                    Component {
                        id: memoryComponent
                        MemoryPage {
                            inUseRamGb: SystemInfo.memoryUsed
                            totalRamGb: SystemInfo.totalMemory
                            loadPercent: SystemInfo.memoryLoadPercent
                            comittedGb: SystemInfo.comittedMemory
                            pageFileString: SystemInfo.pageFile
                        }
                    }

                    Component {
                        id: netComponent
                        Text {
                            text: qsTr("Ethernet")
                        }
                    }

                    Component {
                        id: gpuComponent
                        Text {
                            text: qsTr("GPU")
                        }
                    }
                }
            }
        }
    }
}
