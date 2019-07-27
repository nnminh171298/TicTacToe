import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id: window
    visible: true
    width: 1920 / 3
    height: 1080 / 3
    color: "#424242"
    title: qsTr("Nomi Tic Tac Toe")

    Board {
        id: board
        width: height
        height: parent.height * 5/6 // 900
        color: "#424242"
        anchors.left: parent.left
        anchors.top: parent.top
    }

    MainControl {
        id: mainControl
        width: board.width
        height: parent.height - board.height
        anchors.left: parent.left
        anchors.top: board.bottom

        onSettingClicked: drawer.open();
    }

    AnalysisControl {
        id: analysisControl
        width: parent.width - mainControl.width
        height: mainControl.height
        anchors.bottom: parent.bottom
        anchors.left: mainControl.right
        anchors.right: parent.right
    }

    AnalysisView {
        id: analysisView
        width: analysisControl.width
        height: board.height
        anchors.bottom: analysisControl.top
        anchors.top: parent.top
        anchors.left: board.right
        anchors.right: parent.right
    }

    CustomDrawer {
        id: drawer
        width: window.width / 2
        height: window.height
    }
}
