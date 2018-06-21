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

    Timer
    {
        interval: 500;
        running: true;
        repeat: false
        id:preloadTimer
        onTriggered:
        {
            setComplitionProgressText(0, gameTaskManager.getTaskCount());
        }
    }

    Component.onCompleted:
    {

    }

    Connections
    {
        target:gameTaskManager;

        onTaskComleteEvent:
        {
            gameProgressBar.value = taskNumber * 1.0/allTaskCount;
            setComplitionProgressText(taskNumber, allTaskCount);
        }

        onAllTaskComleteEvent:
        {
            setState("gameOver");
            fullGameTimeText.visible = true;
            fullGameTimeText.text = "Your full time " + (gameTaskManager. getAllTaskCleanTime()).toFixed(1);
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

    ColumnLayout
    {
        x: 540;
        spacing: 20;
        RowLayout {
            spacing: 6;
            Text {
                id:completionText
                text: "Completion 0/0";
                font.family: "Helvetica";
                font.pixelSize: 18;
                color: "#009900";
            }
        }
        RowLayout
        {
            spacing: 6;
            ProgressBar
            {
                id:gameProgressBar;
                value: .0
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 200
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color: "#009900"
                        border.color: "steelblue"
                    }
                }
            }
        }
    }

    Text
    {
        id:gameTimeText;
        text: "Time : " + gameTaskManager.gameTime.toFixed(1);
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#009900";
        x: 1450;
        y: 10;
    }

    Text
    {
        visible: false;
        id:fullGameTimeText;
        text: "Yor Full Time : ";
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#009900";
        x: 540;
        y: -110;
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
        x: 1920
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
            gameTaskManager.stop();
            gameProgressBar.value = 0.0;
            setComplitionProgressText(0, gameTaskManager.getTaskCount());
            fullGameTimeText.visible = false;
            break;

        case "game":
            btnReset.enabled = true;
            btnStart.enabled = false;
            gameProgressBar.value = 0.0;
            gameTaskManager.start();
            setComplitionProgressText(0, gameTaskManager.getTaskCount());
            fullGameTimeText.visible = false;
            break;
        }
    }

    function setComplitionProgressText(taskNumber, allTaskCount)
    {
        completionText.text = "Completion " + taskNumber + "/" + allTaskCount;
    }
}
