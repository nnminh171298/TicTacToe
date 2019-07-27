import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Button {
    id: menuLine
    width: 427
    height: 180

    background: Rectangle {
        border.width: 0
        color: "transparent"
        MouseArea {
            anchors.fill: parent
            onClicked: menuLine.checked = true
        }
    }

    property string title: "Title"
    property string description: "Description"

    ColumnLayout {
        id: textLayout
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: moveNumberText
            text: menuLine.title
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            font.pointSize: Qt.platform.os == "android" ? 14 : 9
            color: menuLine.checked ? "#4DD0E1" : "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        Text {
            id: movePlayerText
            text: menuLine.description
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            font.pointSize: Qt.platform.os == "Android" ? 10 : 7
            color: menuLine.checked ? "#4DD0E1" : "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
}
