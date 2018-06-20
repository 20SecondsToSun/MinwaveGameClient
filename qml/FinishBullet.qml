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
            var finishBulletSize = consts.finishBulletSize;
            visible = true;
            var endPoint = gameTaskManager.getEndPoint();
            x = endPoint.x * consts.scaleFactor - finishBulletSize * 0.5;
            y = consts.canvasY + endPoint.y * consts.scaleFactor - finishBulletSize * 0.5;
        }
    }

    Canvas
    {
        id: canVasBullet;
        width: 50;
        height: 50;
        onPaint:
        {
            var finishBulletSize = consts.finishBulletSize;

            var ctx = getContext("2d");
            ctx.fillStyle = consts.finishBulletColor;
            ctx.ellipse(0, 0, finishBulletSize, finishBulletSize);
            ctx.fill();
        }
    }
}
