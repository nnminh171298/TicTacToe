import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: board
    width: height
    height: 900
    color: "#424242"

    property int subBoardId: -1
    property alias rectBorder: borderRect.border

    Connections {
        target: backend
        onSetCellColor: {
            if(subBoardId == emitted_sub_board_id)
                boardModel.set(cell_index, {"cellColor": cell_color})
        }
    }

    ListModel {
        id: boardModel
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
        ListElement { cellColor: "" }
    }

    GridView {
        id: boardView
        width: parent.width
        height: parent.height
        cellWidth: width/3
        cellHeight: height/3
        anchors.fill: parent
        interactive: false

        model: boardModel
        delegate: Cell {
            width: boardView.cellWidth
            innerColor: cellColor;

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: board.cellMouseEventDisable ? undefined : backend.boardClicked(index)
                // Intro on index
                // https://doc.qt.io/qt-5/qtquick-modelviewsdata-modelview.html#qml-data-models
            }
        }
    }

    Rectangle {
        id: borderRect
        z: 1
        height: parent.width
        width: parent.width
        anchors.bottom: parent.bottom
        color: "transparent"
        border.width: 1
        border.color: "#000000"
    }
}
