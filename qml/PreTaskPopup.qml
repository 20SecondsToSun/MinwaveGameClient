import QtQuick 2.0

Item {
   // width: 300;
   // height: 300;
    visible:false

    Connections
    {
        target:gameTaskManager;

        onUpdateCanvas:
        {
           // canvas.requestPaint();
        }

        onTaskNumberChangedEvent:
        {
            roundText.text = "Round " + (taskNumber+1);
        }

        onAllTaskComleteEvent:
        {
            visible = false;
        }

        onPreTaskStartEvent:
        {
            visible = true;
        }

        onTaskStartEvent:
        {
            visible = false;
        }

        onPreTaskCoundownUpdate:
        {
            countdownText.text = time.toFixed(0);
        }
    }

    Canvas
    {
        id: canvasPopup;
        width: 300;
        height: 300;
        property var canvasColor:  Qt.rgba(0., 0.9, 0., 0.4);

        Component.onCompleted:
        {
            canvasPopup.requestPaint();
        }

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.ellipse(0, 0, 300, 300);
            ctx.fill();
        }

        Text
        {
            anchors.centerIn: parent
            id: roundText
            text: "Round 1";
            font.family: "Helvetica";
            font.pixelSize: 35;
            color: "#ffffff";
            x: 0;
            y: 0;
        }

        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            id: countdownText
            text: "3";
            font.family: "Helvetica";
            font.pixelSize: 30;
            color: "#ffffff";
            x: 0;
            y: 180;
        }
    }
}
