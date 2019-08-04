import QtQuick 2.12
import QtQuick.Controls 2.12

Drawer {
    id: drawer
    width: 640
    height: 1080

    ListModel {
        id: drawerModel
        ListElement { title: "Mode"; isChecked: true }
        ListElement { title: "Help"; isChecked: false }
        ListElement { title: "About"; isChecked: false }
    }

    Rectangle {
        id: lhs
        color: "#616161"
        width: parent.width/3
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        ListView {
            id: lhsView
            anchors.fill: parent
            model: drawerModel
            delegate: ItemDelegate {
                id: item
                width: parent.width
                height: rhs.lineHeight
                autoExclusive: true;
                checked: isChecked
                onCheckedChanged: checked ? rhsView.currentIndex = index : undefined;

                contentItem: Text {
                    text: title
                    font.pointSize: Qt.platform.os == "android" ? 14 : 9
                    color: "#ffffff"
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: parent.checked ? "#424242" : parent.down ? "#424242" : "#616161"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: item.checked = true
                    }
                }
            }
        }
    }

    Rectangle {
        id: rhs
        color: "#424242"
        anchors.left: lhs.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        property int lineHeight: height/6

        Item {
            id: rhsView
            anchors.fill: parent
            property int currentIndex: 0

            MenuMode {
                id: modeMenu
                anchors.fill: parent
                lineHeight: rhs.lineHeight
                visible: parent.currentIndex === 0
            }

            MenuHelp {
                id: helpMenu
                anchors.fill: parent
                lineHeight: rhs.lineHeight
                visible: parent.currentIndex === 1
            }

            MenuAbout {
                id: aboutMenu
                anchors.fill: parent
                lineHeight: rhs.lineHeight
                visible: parent.currentIndex === 2
            }
        }
    }
}
