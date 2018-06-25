import QtQuick 2.0
import "../components"
import "../tests"

Item {
    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

    function setState(state)
    {

    }

    MindwaveComponent
    {
        x:marginLeft
        y:marginTop
        id:mindWave
    }

    LoginTest
    {
        x:marginLeft + 500;
        y:marginTop + 300;

        onLoginState:
        {
            touchWindow.setLoginTestState(state);
        }
    }

    //    LoginModule
    //    {
    //        id:loginModule;
    //        x:marginLeft + 500;
    //        y:marginTop
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
