import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: modeMenu
    color: "#424242"
    property int lineHeight: 135

    ListModel {
        id: modeMenuModel
        ListElement { titleText: "Random (Maybe easy?)"; isChecked: false; descriptionText: "May the force be with you" }
        ListElement { titleText: "Minimax (Easy)"; isChecked: false; descriptionText: "Minimax depth 2" }
        ListElement { titleText: "Minimax (Medium)"; isChecked: true; descriptionText: "Minimax depth 4" }
        ListElement { titleText: "Minimax (Hard)"; isChecked: false; descriptionText: "Minimax full depth" }
    }

    ListView {
        id: modeMenuView
        anchors.fill: parent
        model: modeMenuModel
        delegate: MenuLine {
            id: item
            width: parent.width
            height: lineHeight
            title: titleText
            description: descriptionText
            autoExclusive: true
            checked: isChecked
            onCheckedChanged: {
                modeMenuModel.set(index, { isChecked: checked });
                if(checked)
                    backend.modeChanged(index);
            }
        }
    }
}
