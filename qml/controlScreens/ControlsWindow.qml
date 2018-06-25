import QtQuick 2.0
import "../components"

Item {
    function setState(state)
    {

    }

    MindwaveComponent
    {
        x:marginLeft
        y:marginTop
        id:mindWave
    }

//    LoginModule
//    {
//        id:loginModule;
//        x:marginLeft + 500;
//        y:marginTop
//    }

//    LoginTest
//    {
//        x:marginLeft + 500;
//        y:marginTop + 300;

//        onLoginState:
//        {
//            touchWindow.setLoginTestState(state);
//        }
//    }

//    UserData
//    {
//        x:marginLeft + 900;
//        y:marginTop
//    }

//    GameSession
//    {
//        x:marginLeft + 1200;
//        y:marginTop
//    }

    HealthCheckerComponent
    {
        x:marginLeft;
        y:marginTop + 190
        id:health
    }
}
