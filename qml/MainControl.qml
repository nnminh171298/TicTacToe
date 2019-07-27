import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0

Rectangle {
    id: controlBox
    width: 900
    height: 180
    color: "#424242"
    border.width: 1

    signal settingClicked()

    Switch {
        id: goFirstSwitch
        width: parent.width*7/50
        text: qsTr("Computer 1st")
        checked: true
        display: AbstractButton.TextBesideIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: buttons.right
        anchors.leftMargin: resetButton.width/4

        contentItem: Text {
            text: parent.text
            anchors.leftMargin: parent.width + 10
            anchors.left: parent.left
            font.pointSize: Qt.platform.os == "android" ? 14 : 9
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        indicator: Rectangle {
            implicitWidth: controlBox.width / 9
            implicitHeight: controlBox.height * 13/90
            radius: controlBox.height * 13/90
            x: goFirstSwitch.leftPadding
            anchors.verticalCenter: parent.verticalCenter
            color: goFirstSwitch.checked ? "#00E676" : "#ffffff"
            border.color: goFirstSwitch.checked ? "#00E676" : "#BDBDBD"

            Rectangle {
                width: height
                height: parent.height * 2
                radius: parent.radius
                x: goFirstSwitch.checked ? parent.width - width : 0
                anchors.verticalCenter: parent.verticalCenter
                color: goFirstSwitch.down ? "#BDBDBD" : "#ffffff"
                border.color: "#BDBDBD"
            }
        }
    }

    Rectangle {
        id: buttons
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: childrenRect.width

        CustomButton {
            id: resetButton
            height: parent.height
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            border.width: 0

            icon.source: "/images/play.svg"
            onClicked: {
                backend.reset(goFirstSwitch.checked)
            }
        }

        CustomButton {
            id: settingButton
            height: parent.height
            anchors.left: resetButton.right
            anchors.verticalCenter: parent.verticalCenter
            border.width: 0

            icon.source: "/images/setting.svg"
            onClicked: {
                controlBox.settingClicked()
            }
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
