import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../components"
Item {
    ColumnLayout
    {
        spacing: 20;
        Text
        {
            text: "Login Module";
            font.family: "Helvetica"
            font.pixelSize: 20
            color: "#000099"
        }

        ArduinoComponent
        {
            y:40
        }

        ServerLogin
        {
            y:140
        }
    }
}
