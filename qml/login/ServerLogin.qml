import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

//    anchors {
//        bottom: parent.bottom
//        left: parent.left
//        right: parent.right
//    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Server login";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Text
        {
            id:cleanTimeText;
            text: "response: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
