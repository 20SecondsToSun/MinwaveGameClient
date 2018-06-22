import QtQuick 2.0
import QtQuick.Controls 2.2


//import QtQuick.Layouts 1.3
import "qml"
import "qml/login"
import "qml/components"
import "qml/touchScreens"
import "qml/tests"


ApplicationWindow {
    visible: true
    width: 1700
    height: 580
    title: qsTr("Mind wave client")
    id:core

    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

    Component.onCompleted:
    { 
      // core.showFullScreen();
    }

    //    SocketClient
    //    {
    //        x:marginLeft;
    //        y:marginTop
    //        id:sockets
    //    }

    MindwaveComponent
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

    LoginModule
    {
        id:loginModule;
        x:marginLeft + 500;
        y:marginTop
    }




    LoginTest
    {
        x:marginLeft + 500;
        y:marginTop + 300;

        onLoginState:
        {
            touchWindow.setLoginTestState(state);
        }
    }

    UserData
    {
        x:marginLeft + 900;
        y:marginTop
    }

    GameSession
    {
        x:marginLeft + 1200;
        y:marginTop
    }

    TouchWindow
    {
        id:touchWindow;
    }

    MindwaveGame
    {
        x:marginLeft + 1200;
        y:marginTop + 190
        id:mindWaveGame
    }

    HealthCheckerComponent
    {
        x:marginLeft;
        y:marginTop + 190
        id:health
    }
}
