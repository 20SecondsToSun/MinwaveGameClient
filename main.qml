import QtQuick 2.0
import QtQuick.Controls 2.2


//import QtQuick.Layouts 1.3
import "qml"

ApplicationWindow {
    visible: true
    width: 1700
    height: 480
    title: qsTr("Mind wave client")
    id:core

    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

    Component.onCompleted:
    {
      //
      // aId.start();
      // core.showFullScreen();
    }

    //    SocketClient
    //    {
    //        x:marginLeft;
    //        y:marginTop
    //        id:sockets
    //    }

    MindwaveClient
    {
       // anchors.fill: parent
        focus: true

        Keys.onPressed:
        {
            if (event.key == Qt.Key_Escape) {
                console.log("move left");
                Qt.quit();
            }
        }
        x:marginLeft// + columnShift;
        y:marginTop
        id:mindWave
    }

    UserData
    {
        x:marginLeft + 700;
        y:marginTop
    }

    GameSession
    {
        x:marginLeft + 1000;
        y:marginTop
    }

    MindwaveGame
    {
        x:marginLeft;
        y:marginTop + 130
        id:mindWaveGame
    }
}
