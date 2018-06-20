import QtQuick 2.0

Item
{
    property double scaleFactor: 0.9375;
    property int canvasY: 100;
    property int bulletSize: 20;


    Connections
    {
        target:gameTaskManager;

        onUpdateCanvas:
        {

        }

        onTaskNumberChangedEvent:
        {

        }

        onAllTaskComleteEvent:
        {
           visible = false;
        }

        onPreTaskStartEvent:
        {
            visible = true;
            var startPoint = gameTaskManager.getStartPoint();
            x = startPoint.x * scaleFactor - bulletSize * 0.5;
            y = canvasY + startPoint.y * scaleFactor - bulletSize * 0.5;
        }

        onTaskStartEvent:
        {

        }

        onPreTaskCoundownUpdate:
        {

        }
    }

    Canvas
    {
        id: canVasBullet;
        width: 50;
        height: 50;
        property var canvasColor:  Qt.rgba(0., 0.9, 0., 0.4);

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.ellipse(0, 0, bulletSize, bulletSize);
            ctx.fill();
        }
    }
}
