import QtQuick 2.0
import QtQuick.Controls 2.2
//import QtQuick.Layouts 1.3
import "qml"

ApplicationWindow {
    visible: true
    width: 1400
    height: 1050
    title: qsTr("Mind wave client")
    id:core

    property int marginLeft:50;
    property int marginTop:50;
    property int columnShift:400;

    Component.onCompleted:
    {
        aId.start();
    }

//    SocketClient
//    {
//        x:marginLeft;
//        y:marginTop
//        id:sockets
//    }

    MindwaveClient
    {
        x:marginLeft// + columnShift;
        y:marginTop
        id:mindWave
    }

    MindwaveGame
    {
        x:marginLeft;
        y:marginTop + 180
        id:mindWaveGame
    }
}
