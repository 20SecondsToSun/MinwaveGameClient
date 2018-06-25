import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Item {
    id:root;

    states:
        [
        State{name: "idle";},
        State{name: "game";},
        State{name: "gameOver";}]

    Component.onCompleted:
    {

    }


    Connections
    {
        target:gameTaskManager;      

        onAllTaskComleteEvent:
        {
            setState("gameOver");
         }

        onTaskStartEvent:
        {

        }
    }

    ColumnLayout
    {
        spacing: 20;
        RowLayout {
            spacing: 6;
            Text {
                text: "Mindwave game";
                font.family: "Helvetica";
                font.pixelSize: 18;
                color: "#009900";
            }
        }
        RowLayout {
            spacing: 6;
            Button {
                implicitWidth: 100;
                text: "Start";
                id: btnStart;
                onClicked:
                {
                    setState("game");
                }
            }
            Button {
                implicitWidth: 100;
                text: "Stop";
                id: btnReset;
                enabled:false;
                onClicked:
                {
                    setState("idle");
                }
            }
        }
    }  

    Consts
    {
        id:consts;
    }

    Window {
        objectName: "wnd1"
        visible: true
        id: splash
        // color: "transparent"
        title: "Splash Window"
        // modality: Qt.ApplicationModal
        flags: Qt.SplashScreen
        x: 2920
        width: 1920
        height: 1080

        GameScreen
        {
            id:gamescreen;
        }
    }

    function setState(state)
    {
        root.state = state;
        gamescreen.setState(state);
        switch(state)
        {
        case "gameOver":
            btnReset.enabled = false;
            btnStart.enabled = true;
            break;

        case "idle":
            btnReset.enabled = false;
            btnStart.enabled = true;
            clientService.stopGame();
            break;

        case "game":
            btnReset.enabled = true;
            btnStart.enabled = false;
            clientService.startGame();
            break;
        }
    }

}
