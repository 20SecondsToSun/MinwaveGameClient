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
            text: "GameSession";
            font.family: "Helvetica"
            font.pixelSize: 20
            color: "#000099"
        }
        Text
        {
            text: "SessionTime: " + gameSession.sessionTime.toFixed(1);
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:nonActiveText;
            text: "UserNonActiveTime: 0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
