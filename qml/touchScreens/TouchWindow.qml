import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../components"

import com.app 1.0

Window {
    objectName: "touchWindow"
    visible: true
    id: touchCore
    title: "Splash Window"
    flags: Qt.SplashScreen
    x: 1920
    width: 820
    height: 1080

    function setState(appState)
    {
        hideAll();
        switch(appState)
        {
        case AppState.Login:
             loginScreen.visible = true;
            break;

        case AppState.Instruction:
            console.log("touchWindow app state changes :::::::::::::", appState);
             instructionScreen.visible = true;
            break;
        }
    }

    LoginScreen
    {
        id: loginScreen;
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
            loginScreen.visible = true;
        }
    }

    function hideAll()
    {
        loginScreen.visible = false;
        instructionScreen.visible = false;
        gameScreen.visible = false;
        loginScreen.reset();
        instructionScreen.reset();
        gameScreen.reset();

    }
}
