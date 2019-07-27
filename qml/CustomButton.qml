import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: button
    width: height
    height: 180
    display: AbstractButton.IconOnly

    property alias radius: backRect.radius
    property alias border: backRect.border

    background: Rectangle {
        id: backRect
        color: button.pressed ? "#616161" : "#424242"
        border.color: "#000000"
        border.width: 0
    }

    icon.color: button.enabled? "#00E676" : "#9E9E9E"
}
