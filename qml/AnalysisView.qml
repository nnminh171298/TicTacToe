import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: analysisView
    width: 1020
    height: 900
    color: "#424242"
    border.width: 1

    property bool isVertical: height > width
    property int subBoardLoaded: 0
    function onSubBoardLoaded(){
        subBoardLoaded++;
        if(subBoardLoaded == model.count)
            backend.reset(true)
    }

    Connections {
        target: backend
        onSetIndicatorColor: {
            model.set(sub_board_index, {"indicatorColor": indicator_color})
        }
    }

    ListModel {
        id: model
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
        ListElement { indicatorColor: "" }
    }

    GridView {
        id: view
        width: (isVertical ? parent.width : parent.height) * 30/32
        height: width
        cellWidth: width/3
        cellHeight: cellWidth
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        model: model
        delegate: Rectangle {
            width: view.cellWidth
            height: width
            color: analysisView.color

            Board {
                id: subBoard
                height: view.width * 8/30
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                Circle {
                    z: 2
                    width: parent.width/10
                    color: indicatorColor
                    anchors.horizontalCenter: parent.right
                    anchors.verticalCenter: parent.bottom
                }

                subBoardId: index
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: backend.boardClicked(index)
                    onPressedChanged: parent.rectBorder.width = pressed ? 2 : 1
                }

                Component.onCompleted: analysisView.onSubBoardLoaded();
            }
        }
    }
}
