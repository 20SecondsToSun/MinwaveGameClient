import QtQuick 2.0

Item
{
    property double nextAttentionValue: 0.0;

    Consts
    {
        id:consts;
    }

    Connections
    {
        target:mind;
        onAttentionChanged:
        {
            nextAttentionValue = mind.attention / 100.0;


            attentionAnim.to = nextAttentionValue;
            attentionAnim.duration = 1000;
            attentionAnim.start();
        }
    }

    Connections
    {
        target:gameTaskManager;

        onAllTaskComleteEvent:
        {
            visible = true;
        }

        onUpdateCanvas:
        {
           // console.log("nextAttentionValue ", nextAttentionValue);
            canvasCirc.requestPaint();
            updatePosition();
        }

        onPreTaskStartEvent:
        {
            canvasCirc.percentLimit = gameTaskManager.getMindwaveLimit();
            visible = true;
            updatePosition();
        }
    }

    function updatePosition()
    {
        var startPoint = gameTaskManager.getCurPoint();
        x = startPoint.x * consts.scaleFactor - canvasCirc.width * 0.5;
        y = consts.canvasY + startPoint.y * consts.scaleFactor - canvasCirc.height * 0.5;

    }

    function setLimitPersent(percent)
    {
        canvasCirc.percentLimit = percent;
    }

    Canvas
    {

        id: canvasCirc;
        width: 250;
        height: 250;
        property int centerWidth: 250 * 0.5
        property int centerHeight: 250 * 0.5
        property int radius: 80;

        property real percentLimit: 0.0;
        property real percentAttention: 0.0;


        onPaint:
        {
            var colorBg = Qt.rgba(0., 164./255., 227.0 / 255., 0.3);
            var colorLimit = Qt.rgba(232./ 255., 187./255., 6.0 / 255., 0.5);
            var colorAttention = Qt.rgba(0., 164./255., 227.0 / 255., 1.3);
            var lineWidth = 10;

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, 250, 250);

            ctx.strokeStyle = consts.redColor;
            ctx.lineCap = consts.lineCap;
            ctx.lineJoin = consts.lineJoin;

            ctx.lineWidth = lineWidth;

            ctx.strokeStyle = colorBg;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2*Math.PI);
            ctx.stroke();
            ctx.closePath();

            ctx.strokeStyle = colorLimit;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2*Math.PI * canvasCirc.percentLimit);
            ctx.stroke();
            ctx.closePath();

            ctx.strokeStyle = colorAttention;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2*Math.PI * canvasCirc.percentAttention);
            ctx.stroke();
            ctx.closePath();
        }

        PropertyAnimation
        {
            id: attentionAnim;
            target: canvasCirc;
            property: "percentAttention";
            to: 100;
            duration: 500
        }
    }
}
