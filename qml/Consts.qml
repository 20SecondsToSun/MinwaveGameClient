import QtQuick 2.0

Item {

    property int lineWidth: 10;
    property string lineCap: "round";
    property string lineJoin: "round";
     property int bulletSize: 20;

    property int carAddAngle: -90;
    property int carWidth: 30;
    property int carHeight: 54;

    property double scaleFactor: 0.9375;
    property int canvasY: 100;
    property var redColor: Qt.rgba(0.9, 0.0, 0.0, 1);

    property var finishBulletColor:  Qt.rgba(0.6, 0.6, 0.6, 1.);
    property var startBulletColor:  Qt.rgba(0.9, 0.0, 0.0, 1);


    property var guideColor: Qt.rgba(0.6, 0.6, 0.6, animateHelper.opacity);

    property double toDegrees: 180 / Math.PI;
    Item {
        id: animateHelper
        opacity: 0
        PropertyAnimation { id: opacityAnimtor;
            target: animateHelper;
            property: "opacity";
            from: 0;
            to: 1;
            duration: 500 }
    }

    function animateGuideColor()
    {
        opacityAnimtor.start();
    }
}
