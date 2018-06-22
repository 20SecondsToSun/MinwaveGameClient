import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {

    id:backcore

    signal back();

    Button
    {
        id: backBtn
        text:"back"
        visible:true
        onClicked:
        {
            backcore.back();
        }
    }

}
