import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../components"

Window {
    objectName: "touchWindow"
    visible: true
    id: touchCore
    title: "Splash Window"
    flags: Qt.SplashScreen
    x: 1920
    width: 820
    height: 1080

    function setLoginTestState(state)
    {
        helloScreen.setTestState(state);
    }

    Component.onCompleted:
    {
        instructionScreen.visible = false;
    }

    HelloScreen
    {
        id: helloScreen;

        onStart:
        {
            helloScreen.visible = false;
            instructionScreen.visible = true;
        }
    }

    InstructionScreen
    {
        id: instructionScreen;
        visible: false
    }

    GameScreen
    {
        id: gameScreen;
        visible: false
    }

    HealthCheckerComponent
    {
        id:health
        y: 1000
        x: 50
    }

    BackBtn
    {
        id:backBtn
        x: 720
        y: 100

        onBack:
        {
            hideAll();
            helloScreen.visible = true;
        }
    }

    function hideAll()
    {
        helloScreen.visible = false;
        instructionScreen.visible = false;
        gameScreen.visible = false;
        helloScreen.reset();
        instructionScreen.reset();
        gameScreen.reset();

    }
}
