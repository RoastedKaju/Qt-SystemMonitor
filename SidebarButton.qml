import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts

Button {
    id: btn
    Layout.preferredWidth: 135
    Layout.preferredHeight: 50
    text: "JUST A BUTTON"

    background: Rectangle {
        radius: 5
        border.color: "transparent"

        color: btn.down
               ? "#EB5B00"
               : btn.hovered
                 ? "#FFE52A"
                 : "#FFCC00"
    }

    contentItem: Text {
        text: btn.text
        color: "#2F2F2F"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
