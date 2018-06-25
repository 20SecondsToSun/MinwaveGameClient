import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4



Item {
    id: loginTest
    signal loginState(int state);

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Login Test";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#009999"
        }

        Button
        {
            text:"Login success / first time"
            onClicked:
            {
                loginModule.loginSuccessTest();
            }
        }

        Button
        {
            text:"Login success / second time"
            onClicked:
            {
               loginTest.loginState(2);
            }
        }

        Button
        {
            text:"Wait you played resent"
            onClicked:
            {
               loginTest.loginState(3);
            }
        }

        Button
        {
            text:"User doesn't exist"
            onClicked:
            {
               loginTest.loginState(400);
            }
        }

        Button
        {
            text:"Module error"
            onClicked:
            {
               loginTest.loginState(401);
            }
        }

    }

}
