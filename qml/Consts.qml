import QtQuick 2.0

Item {

    property int lineWidth: 5;
    property string lineCap: "round";
    property string lineJoin: "round";
    property int bulletSize: 10;
    property int finishBulletSize: finBulletSizeAnimateHelper.size;

    property int carAddAngle: -90 + 180;
    property int carWidth: 64;//30;
    property int carHeight: 124;//54;

    property double scaleFactor: 1.25;//9375;
    property double artScaleFactor: 0.925;
    property int canvasY: 100;


    property var redColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var finishBulletColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var startBulletColor:  Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var guideColor: Qt.rgba(0.9, 0.9, 0.9, animateHelper.opacity);

    property double toDegrees: 180 / Math.PI;
    Item {
        id: animateHelper
        opacity: 0
        PropertyAnimation { id: opacityAnimtor;
            target: animateHelper;
            property: "opacity";
            from: 0;
            to: 0.5;
            duration: 500 }
    }

    Item {
        id: finBulletSizeAnimateHelper
        property int size: 40;
        PropertyAnimation { id: sizeAnimtor;
            target: finBulletSizeAnimateHelper;
            property: "size";
            from: 10;
            to: 20;
            duration: 500
        }
    }

    function animateGuideColor()
    {
        sizeAnimtor.start();
        opacityAnimtor.start();
    }
}
