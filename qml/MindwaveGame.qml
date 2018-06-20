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

        onUpdateCanvas:
        {
            canvas.requestPaint();
        }

        onTaskComleteEvent:
        {
            gameProgressBar.value = taskNumber * 1.0/allTaskCount;
            setComplitionProgressText(taskNumber, allTaskCount);
        }

        onAllTaskComleteEvent:
        {
            setState("gameOver");
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
        x: 1040;
        y: 10;
    }

    property double scaleFactor: 0.9375;

    Canvas
    {
      // visible:false
        id: canvas;
        width: 1200;
        height: 675;
        y: 100;
        property var canvasColor:  Qt.rgba(0.6, 0.6, 0.6, 1);
        property string heroView: "qrc:/resources/car.png";
        property string roadView: "qrc:/resources/road.jpg";


        Component.onCompleted:
        {
            loadImage(heroView);
            loadImage(roadView);
        }

        onImageLoaded:
        {

            canvas.requestPaint();
        }



        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.fillRect(0, 0, width, height);
            ctx.drawImage(roadView, 0, 0);


            if(gameTaskManager.isPreTaskState())
            {
               drawGuidePaths(ctx);
               moveCar();
            }

            if(gameTaskManager.isRunning())
            {
                drawGuidePaths(ctx);
               // drawPrevPaths(ctx);

                var list = gameTaskManager.getCompletedPath();

                ctx.lineWidth = 10;
                ctx.strokeStyle = "red";
                ctx.lineCap = "round";
                ctx.lineJoin = "round";


                if(list.length > 1)
                {
                    ctx.beginPath();
                    ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
                    for(var i = 1; i < list.length; i++)
                    {
                        ctx.lineTo(list[i].x * scaleFactor, list[i].y * scaleFactor);
                    }
                }
                else
                {
                    ctx.beginPath();
                    var startPoint = gameTaskManager.getStartPoint();
                    ctx.moveTo(startPoint.x * scaleFactor, startPoint.y * scaleFactor);
                }

                var curPoint = gameTaskManager.getCurPoint();
                ctx.lineTo(curPoint.x * scaleFactor, curPoint.y * scaleFactor);
                ctx.stroke();
                ctx.closePath();

                moveCar();

            }
        }
    }

    Image
    {
       id:car
       visible: false;
       y: 100;
       width: 49; height: 88
       source: "qrc:/resources/car.png"
       transform: Translate { x: -car.width * 0.5; y: car.height * 0.5 }
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
            car.visible = false;
            break;

        case "idle":
            btnReset.enabled = false;
            btnStart.enabled = true;
            gameTaskManager.stop();
            gameProgressBar.value = 0.0;
            car.visible = false;
            setComplitionProgressText(0, gameTaskManager.getTaskCount());
            break;

        case "game":
            btnReset.enabled = true;
            btnStart.enabled = false;
             gameProgressBar.value = 0.0;
            canvas.canvasColor = Qt.rgba(0.6, 0.6, 0.6, 1);
            gameTaskManager.start();
            setComplitionProgressText(0, gameTaskManager.getTaskCount());
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
        ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
        ctx.strokeStyle = "gray"
        ctx.lineWidth = 8;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x * scaleFactor, list[i].y * scaleFactor);
        }
        ctx.stroke();
        ctx.closePath();
    }

    function moveCar()
    {
        var curPoint = gameTaskManager.getCurPoint();

        car.x = curPoint.x * scaleFactor;
        car.y = curPoint.y * scaleFactor;
        car.visible = true;

        var rotation = gameTaskManager.getForwardVectorRotation();
        var degrees = rotation * 180 / Math.PI;
        car.rotation = degrees - 90;
    }

    function setComplitionProgressText(taskNumber, allTaskCount)
    {
        completionText.text = "Completion " + taskNumber + "/" + allTaskCount;
    }
}
