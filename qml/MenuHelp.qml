import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle {
    id: helpMenu
    color: "#424242"
    property int lineHeight: 135

    ListModel {
        id: aboutMenuModel
        ListElement { titleText: "Win indicator"; indicatorColor: "#f44336"; descriptionText: "Player (will) win" }
        ListElement { titleText: "Lose indicator"; indicatorColor: "#2196f3"; descriptionText: "Computer (will) win" }
        ListElement { titleText: "Tie indicator"; indicatorColor: "#CDDC39"; descriptionText: "Not again..." }
        ListElement { titleText: "Unknown indicator"; indicatorColor: "#616161"; descriptionText: "I'm a dumb bot. IDK :D" }
    }

    ListView {
        id: aboutMenuView
        anchors.fill: parent
        model: aboutMenuModel
        delegate: Rectangle {
            height: lineHeight
            width: aboutMenuView.width
            color: "transparent"

            Rectangle {
                id: indicatorRect
                color: "transparent"
                height: lineHeight / 2
                width: lineHeight / 2
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                Circle {
                    id: indicator
                    width: lineHeight / 4
                    color: indicatorColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            MenuLine {
                width: parent.width * 3/4
                height: lineHeight
                anchors.left: indicatorRect.right
                title: titleText
                description: descriptionText
                onCheckedChanged: checked = false
            }
        }
    }
}
