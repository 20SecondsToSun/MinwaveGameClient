import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:root;

    states:
        [
        State{name: "idle";},
        State{name: "game";},
        State{name: "gameOver";}]

    Connections
    {
        target:gameTaskManager;

        onUpdateCanvas:
        {
            canvas.requestPaint();
        }

        onTaskComleteEvent:
        {
            gameProgressBar.value = taskNumber * 1.0/allTaskCount;
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

    RowLayout
    {
        x: 540;
        y: 10;
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

    Text
    {
        id:gameTimeText;
        text: "Time : " + gameTaskManager.gameTime.toFixed(1);
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#009900";
        x: 1040;
        y: 10;
    }

    Canvas
    {
        id: canvas;
        width: 1200;
        height: 600;
        y: 100;
        property var canvasColor:  Qt.rgba(0.6, 0.6, 0.6, 1);
        property string heroView: "qrc:/resources/car.jpg";
        Component.onCompleted:loadImage(heroView);

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.fillRect(0, 0, width, height);

            if(gameTaskManager.isRunning())
            {
                drawGuidePaths(ctx);
                drawPrevPaths(ctx);

                var startPoint = gameTaskManager.getStartPoint();

                ctx.beginPath();
                ctx.lineWidth = 10;
                ctx.strokeStyle = "red";
                ctx.moveTo(startPoint.x, startPoint.y);
                var curPoint = gameTaskManager.getCurPoint();
                ctx.lineTo(curPoint.x, curPoint.y);
                ctx.stroke();
                ctx.closePath();
                ctx.drawImage(heroView, curPoint.x, curPoint.y);
            }
        }
    }

    function setState(state)
    {
        root.state = state;
        switch(state)
        {
        case "gameOver":
            canvas.canvasColor = Qt.rgba(0.0, 0.6, 0.0, 1);
            btnReset.enabled = false;
            btnStart.enabled = true;
            break;

        case "idle":
            btnReset.enabled = false;
            btnStart.enabled = true;
            gameTaskManager.stop();
            gameProgressBar.value = 0.0;
            break;

        case "game":
            btnReset.enabled = true;
            btnStart.enabled = false;
            canvas.canvasColor = Qt.rgba(0.6, 0.6, 0.6, 1);
            gameTaskManager.start();

            break;
        }
    }

    function drawPrevPaths(ctx)
    {
        var list = gameTaskManager.getCompletedPath();
        if(list.length > 1)
        {
            ctx.beginPath();
            ctx.lineWidth = 10;
            ctx.strokeStyle = "red";
            ctx.moveTo(list[0].x, list[0].y);

            for(var i = 1; i < list.length; i++)
            {
                ctx.lineTo(list[i].x, list[i].y);
            }
            ctx.stroke();

            ctx.closePath();
        }
    }

    function drawGuidePaths(ctx)
    {
        var list = gameTaskManager.getFullPath();

        ctx.beginPath()
        ctx.moveTo(list[0].x, list[0].y);
        ctx.strokeStyle = "gray"
        ctx.lineWidth = 8;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x, list[i].y);
        }
        ctx.stroke();
        ctx.closePath();
    }


}
