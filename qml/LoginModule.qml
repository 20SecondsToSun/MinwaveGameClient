import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

Item {

    Settings {
            category:"login"
            id: settings
            property string login;
            property string pass;
        }

    Component.onCompleted:
    {
        console.log("login ::: ", settings.login);
    }

    Connections
    {
        target:loginService;
        onLoginSuccess:
        {

        }
        onLoginFailed:
        {
            content.enabled = true;
            btnConnect.text = "Login";
        }

        onStartLogin:
        {
            content.enabled = false;
            btnConnect.text = "Logining...";
        }
    }

    GroupBox {
        id: content;
        x: (window.width - content.width)*0.5;
        y: (window.height - content.height)*0.5;
        ColumnLayout
        {
            spacing: 6;
            TextField {
                id: login;
                implicitWidth: 300;
                text: settings.login;
                placeholderText: qsTr("login");
            }
            TextField {
                id: pass;
                implicitWidth: 300
                placeholderText: qsTr("password");
                text: settings.pass;
                echoMode:TextInput.Password
            }
            Button {
                implicitWidth: 300;
                implicitHeight:50;
                text: "Login";
                id: btnConnect;
                onClicked:
                {
                    settings.pass = pass.text;
                    settings.login = login.text;
                    loginService.login(login.text, pass.text);
                }

                background: Rectangle
                {
                    id:btnColor;
                    opacity: 0.7
                    color: "#ffffff"
                }
            }
        }
    }
}
