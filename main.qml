import QtQml.Models 2.3
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

ApplicationWindow {
    id: window
    visible: true
    width: 540
    height: 780
    title: "Tic Tac Toe"
    background: Rectangle { color: "#dcffff" }

    header: ToolBar {
        width: parent.width
        spacing: 0
        RowLayout {
            width: parent.width
            spacing: 0
            ToolButton {
                id: playerFirstButton
                implicitWidth: parent.width * 0.4
                text: "Player 1st"
                icon.source: "images/icon-player.png"
                onClicked: backend.playerFirstButtonClicked();
            }
            ToolButton {
                id: computerFirstButton
                implicitWidth: parent.width * 0.4
                text: "Computer 1st"
                icon.source: "images/icon-computer.png"
                onClicked: backend.computerFirstButtonClicked();
            }
            BusyIndicator {
                id: busyIndicator
                implicitWidth: parent.width * 0.2
                implicitHeight: parent.height
            }
        }
    }

    ListModel {
        id: boardModel
        ListElement { name: "cell_1"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_2"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_3"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_4"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_5"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_6"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_7"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_8"; image_source: "qrc:/images/blank.png" }
        ListElement { name: "cell_9"; image_source: "qrc:/images/blank.png" }
    }

    Column {
        spacing: 20
        padding: 10
        width: parent.width - padding * 2
        Rectangle {
            width: parent.width
            height: parent.width
            border.width: 2
            border.color: "black"
            GridView {
                id: boardView
                width: parent.width - 4
                height: width
                cellWidth: width/3
                cellHeight: height/3
                anchors.centerIn: parent
                currentIndex: -1

                model: boardModel
                delegate: imageDelegate
            }
        }

        Row {
            spacing: 0
            width: parent.width
            Label {
                width: parent.width * 0.5
                text: "Board status:"
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: text_status
                width: parent.width * 0.5
                readOnly: true
                Layout.fillWidth: true
            }
        }

        Row {
            spacing: 0
            width: parent.width
            Label {
                width: parent.width * 0.5
                text: "Computer choices:"
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: text_choices
                width: parent.width * 0.5
                readOnly: true
                Layout.fillWidth: true
            }
        }

        Row {
            spacing: 0
            width: parent.width
            Label {
                width: parent.width * 0.5
                text: "Computer analysis:"
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: text_analysis
                width: parent.width * 0.5
                readOnly: true
                Layout.fillWidth: true
            }
        }
    }

    Component {
        id: imageDelegate
        Rectangle {
            width: boardView.cellWidth
            height: boardView.cellHeight
            border.color: "black"
            Column {
                anchors.centerIn: parent
                Image {
                    source: image_source
                    width: boardView.cellWidth - 15
                    height: boardView.cellHeight - 15
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    boardView.currentIndex = index
                    backend.boardClicked(index)
                }
            }
        }
    }

    Connections {
        target: backend
        onReset: {
            boardModel.set(0, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(1, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(2, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(3, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(4, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(5, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(6, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(7, {"image_source": "qrc:/images/blank.png"})
            boardModel.set(8, {"image_source": "qrc:/images/blank.png"})
        }
        onDisplayMove: {
            boardModel.set(index, {"image_source": imageSource})
            text_choices.text = computerChoicesString
            displayAnalysis(computerAnalysisValue)
        }
        onUpdateBoardStatus: displayBoardStatus(status)
        onReady: {
            busyIndicator.running = false
            playerFirstButton.implicitWidth = playerFirstButton.parent.width * 0.5
            computerFirstButton.implicitWidth = computerFirstButton.parent.width * 0.5
        }
    }

    function displayAnalysis(computerAnalysisValue) {
        switch(computerAnalysisValue) {
        case 0:
            text_analysis.text = "It's a tie"
            text_analysis.palette.base = "cyan"
            break
        case 127:
            text_analysis.text = "Computer wins"
            text_analysis.palette.base = "lime"
            break
        case -128:
            text_analysis.text = "Computer loses"
            text_analysis.palette.base = "red"
            break
        }
    }

    function displayBoardStatus(status) {
        switch(status) {
        case 0:
            text_status.text = "Computer loses"
            text_status.palette.base = "red"
            break
        case 1:
            text_status.text = "Computer wins"
            text_status.palette.base = "lime"
            break
        case 2:
            text_status.text = "It's a tie"
            text_status.palette.base = "cyan"
            break
        case 3:
            text_status.text = "Unknown"
            text_status.palette.base = "yellow"
            break
        }
    }
}
