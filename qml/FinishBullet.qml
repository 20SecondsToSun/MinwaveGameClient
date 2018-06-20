import QtQuick 2.0

Item
{
    Consts
    {
        id:consts;
    }

    Connections
    {
        target:gameTaskManager;

        onAllTaskComleteEvent:
        {
           visible = false;
        }

        onPreTaskStartEvent:
        {
            visible = true;
            var endPoint = gameTaskManager.getEndPoint();
            x = endPoint.x * consts.scaleFactor - consts.bulletSize * 0.5;
            y = consts.canvasY + endPoint.y * consts.scaleFactor - consts.bulletSize * 0.5;
        }
    }

    Canvas
    {
        id: canVasBullet;
        width: 50;
        height: 50;
        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = consts.finishBulletColor;
            ctx.ellipse(0, 0, consts.bulletSize, consts.bulletSize);
            ctx.fill();
        }
    }
}
