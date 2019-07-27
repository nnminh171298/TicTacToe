import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle {
    id: analysisControl
    width: 1020
    height: 180
    color: "#424242"
    border.width: 1

    Connections {
        target: backend
        onSetAnalysisText: {
            movePlayerText.text = str;
        }
        onSetAnalysisNum: {
            moveNumberText.text = str;
        }
        onSetUndoEnable: {
            undoButton.enabled = enable
        }
        onSetRedoEnable: {
            redoButton.enabled = enable
        }
    }

    CustomButton {
        id: undoButton
        z: 1
        height: parent.height
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        icon.source: "/images/undo.svg"
        onClicked: {
            backend.undoClicked()
        }
    }

    CustomButton {
        id: redoButton
        z: 1
        height: parent.height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        icon.source: "/images/redo.svg"
        onClicked: {
            backend.redoClicked()
        }
    }

    ColumnLayout {
        id: textLayout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: moveNumberText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pointSize: Qt.platform.os == "android" ? 16 : 10
            font.bold: true
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: movePlayerText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pointSize: Qt.platform.os == "android" ? 14 : 9
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        id: borderRect
        z: 10
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: "#000000"
    }
}
