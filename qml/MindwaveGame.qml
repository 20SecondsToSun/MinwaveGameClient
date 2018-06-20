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
            fullGameTimeText.visible = true;
            fullGameTimeText.text = "Your full time " + (gameTaskManager. getAllTaskCleanTime()).toFixed(1);
        }

        onPreTaskStartEvent:
        {
            consts.animateGuideColor();
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
        x: 1040;
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

    Canvas
    {
        id: canvas;
        width: 1200;
        height: 675;
        y: consts.canvasY;
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
            var scaleFactor = consts.scaleFactor;
            var ctx = getContext("2d");
            ctx.drawImage(roadView, 0, 0);

            if(gameTaskManager.isPreTaskState())
            {
                drawGuidePaths(ctx);
                moveCar();
            }

            if(gameTaskManager.isRunning())
            {
                drawGuidePaths(ctx);
                var list = gameTaskManager.getCompletedPath();

                ctx.lineWidth = consts.lineWidth;
                ctx.strokeStyle = consts.redColor;
                ctx.lineCap = consts.lineCap;
                ctx.lineJoin = consts.lineJoin;

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

    FinishBullet
    {
        id:finishBullet
        visible: false;
        y: consts.canvasY;
    }

    StartBullet
    {
        id:startBullet
        visible: false;
        y: consts.canvasY;
    }

    Image
    {
        id:car
        visible: false;
        y: consts.canvasY;
        width: consts.carWidth;
        height: consts.carHeight;
        source: "qrc:/resources/car.png"
        transform: Translate { x: -car.width * 0.5; y: -car.height * 0.5 }
    }

    PreTaskPopup
    {
        id:pretaskPopup
        x:canvas.width - 300 - 10;
        y:100 + 10;
    }

    function setState(state)
    {
        root.state = state;
        switch(state)
        {
        case "gameOver":
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
            pretaskPopup.visible = false;
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

    function drawGuidePaths(ctx)
    {
        var scaleFactor = consts.scaleFactor;
        var list = gameTaskManager.getFullPath();

        ctx.beginPath()
        ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
        ctx.strokeStyle =  consts.guideColor;
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
        var scaleFactor = consts.scaleFactor;
        var canvasY = consts.canvasY;

        var curPoint = gameTaskManager.getCurPoint();

        car.x = curPoint.x * scaleFactor;
        car.y = canvasY + curPoint.y * scaleFactor;
        car.visible = true;

        var rotation = gameTaskManager.getForwardVectorRotation();
        var degrees = rotation * consts.toDegrees;
        car.rotation = degrees + consts.carAddAngle;
    }

    function setComplitionProgressText(taskNumber, allTaskCount)
    {
        completionText.text = "Completion " + taskNumber + "/" + allTaskCount;
    }
}
