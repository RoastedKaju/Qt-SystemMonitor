import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

Button {
    id: control
    Layout.preferredWidth: 135
    Layout.preferredHeight: 50
    text: "TEXT"

    background: Rectangle {
        radius: 5
        border.color: "transparent"
        color: control.down      ? "#EB5B00" :
               control.checked   ? "#EB5B00" :
               control.hovered   ? "#FFE52A" :
                                   "#FFCC00"
    }

    contentItem: Text {
        text: control.text
        color: "#2F2F2F"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
