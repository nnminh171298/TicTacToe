import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: modeMenu
    color: "#424242"
    property int lineHeight: 135

    ListModel {
        id: modeMenuModel
        // the title text before " (" have to match with Algo.getAlgoName()
        ListElement { titleText: "Minimax (Hard)"; isChecked: true; descriptionText: "Result from minimax algorithm" }
        ListElement { titleText: "Fill blank (Easy)"; isChecked: false; descriptionText: "Fill the first empty cell found" }
        ListElement { titleText: "Random (Maybe easy?)"; isChecked: false; descriptionText: "May the force be with you" }
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
                    backend.modeChanged(titleText);
            }
        }
    }
}
