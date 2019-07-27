import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
     width: parent.width < parent.height ? parent.width : parent.height
     height: width
     border.color: "black"
     border.width: 1
     radius: width*0.5
}
