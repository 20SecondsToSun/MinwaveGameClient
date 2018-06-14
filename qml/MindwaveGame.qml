import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    id:root;

    states:
        [
        State{name: "idle";},
        State{name: "game";},
        State{name: "gameOver";}]

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

    Text
    {
        id:gameTimeText;
        text: "Time : 0.0";
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
        height: 200;
        y: 100;
        property var canvasColor:  Qt.rgba(0.6, 0.6, 0.6, 1);
        property string heroView: "qrc:/resources/car.png";
        Component.onCompleted:loadImage(heroView);

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.fillRect(0, 0, width, height);
            ctx.drawImage(canvas.heroView, hero.locationX, hero.locationY);
        }
    }

    property double finalPosition: 960;
    property double startGameTime: 0;

    MindwaveHero
    {
        id:hero;

        property double locationX: 0;
        property double locationY: 40;
        property double velocity: 0;

        property double dataThresholdMax: 100;

        property double minVelocity: 0;
        property double maxVelocity: 3;

        property double minVelocity1: -5;
        property double maxVelocity1: -1;

        Timer
        {
            id:gameTimer;
            interval: 10;
            repeat: true;

            onTriggered:
            {
                gameTimeText.text = "Time: " + ((new Date().getTime() - startGameTime) / 1000.).toFixed(1);

                if(hero.locationX >= finalPosition)
                {
                    hero.locationX = finalPosition;
                    setState("gameOver");
                }

                var value = 0;
                if (root.state == 'game' && core.gameStrategy == 1)
                {
                    value = mind.attention;
                }
                else if (root.state == 'game' && core.gameStrategy == 2)
                {
                    value = mind.meditation;
                }

                if(value > hero.dataThresholdMin)
                {
                    hero.velocity = map(value, hero.dataThresholdMin,  hero.dataThresholdMax, hero.minVelocity,  hero.maxVelocity);
                }
                else if (core.backMove)
                {
                    hero.velocity = map(value, 0, core.dataThresholdMin,  hero.minVelocity1, hero.maxVelocity1);
                }

                hero.locationX += hero.velocity;

                if(hero.locationX <= 0)
                {
                    hero.locationX = 0;
                }

                canvas.requestPaint();
            }
        }

        PropertyAnimation
        {
            id: heroAnim;
            target: hero;
            property: "locationX";
            to: 100;
            duration: 1000
        }
    }

    function setState(state)
    {
        root.state =state;
        switch(state)
        {
        case "gameOver":
            gameTimer.stop();
            canvas.canvasColor = Qt.rgba(0.0, 0.6, 0.0, 1);
            btnReset.enabled = false;
            btnStart.enabled = true;
            break;

        case "idle":
            hero.locationX = 0;
            btnReset.enabled = false;
            btnStart.enabled = true;
            heroAnim.stop();
            gameTimer.stop();
            break;

        case "game":
            hero.locationX = 0;
            btnReset.enabled = true;
            btnStart.enabled = false;
            startGameTime = new Date().getTime();
            gameTimer.start();
            canvas.canvasColor = Qt.rgba(0.6, 0.6, 0.6, 1);
            break;
        }
    }

    function map(x, in_min, in_max, out_min, out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}
