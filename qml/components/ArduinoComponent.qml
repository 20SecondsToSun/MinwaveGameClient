import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Arduino component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Text
        {
            id:com;
            text: "com: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:baudRate;
            text: "baudRate: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }


        Text
        {
            id:conStatus;
            text: "connection status: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "arduino data: 0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
