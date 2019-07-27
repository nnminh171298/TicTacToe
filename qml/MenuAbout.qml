import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: aboutMenu
    color: "#424242"
    property int lineHeight: 135

    ListModel {
        id: aboutMenuModel
        ListElement { titleText: ""; descriptionText: "Developed using Qt" }
        ListElement { titleText: "Developer"; descriptionText: "Nguyen Ngoc Minh" }
        ListElement { titleText: "Contact"; descriptionText: "ngocminh171298@gmail.com" }
        ListElement { titleText: "Note"; descriptionText: "Thank you for playing!" }
    }

    Component.onCompleted: aboutMenuModel.set(0, { "titleText": "Nomi Tic Tac Toe v" + Qt.application.version })
    ListView {
        id: aboutMenuView
        anchors.fill: parent
        model: aboutMenuModel
        delegate: MenuLine {
            width: parent.width
            height: lineHeight
            title: titleText
            description: descriptionText
            onCheckedChanged: checked = false
        }
    }
}
