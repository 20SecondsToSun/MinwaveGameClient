import QtQuick 2.0
import QtQuick.Controls 2.2

import QtQuick.Window 2.2
//import QtQuick.Layouts 1.3
import "qml"

ApplicationWindow {
    visible: true
    width: 1700
    height: 1080
    title: qsTr("Mind wave client")
    id:core

    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

//    Item {

//        Window {
//            objectName: "wnd1"
//            visible: true
//        }

//        Window {
//            objectName: "wnd2"
//            visible: true
//        }
//    }


    Component.onCompleted:
    {
      //
        //aId.start();

        core.showFullScreen();
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

    MindwaveGame
    {
        x:marginLeft;
        y:marginTop + 90
        id:mindWaveGame
    }
}
