import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: cell
    color: "transparent"
    property alias innerColor: innerRec.color
    property bool isColored: innerColor != "#616161"
    width: 300
    height: width
    border.width: 1
    border.color: "#000000"

    Rectangle {
        id: innerRec
        width: parent.width*0.8
        height: parent.height*0.8
        color: "#616161"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        border.color: color
    }
}
