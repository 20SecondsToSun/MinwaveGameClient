import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
//import com.network 1.0

Item {
    id:root;
    height: content.height;
    property var model;

    signal connect(string ip, string port);
    signal disconnect();
    signal autoConnectChanged(bool value);

    Connections
    {
        target: socketClient;

        onConnectionStatusChanged:
        {
            if(status == 2)
            {
                statusText.text = "Connected";
                statusText.color = "#009900";
                btnDisconnect.enabled = true;
                btnConnect.enabled = false;
            }
            else if(status == 3)
            {
                statusText.text = "Disconnected";
                statusText.color = "#990000";
                btnDisconnect.enabled = false;
                btnConnect.enabled = true;
            }
        }
    }

    ColumnLayout{
        spacing: 20;
        RowLayout {
            spacing: 6;
            Text {
                text: "Connection to Game Server";
                font.family: "Helvetica"
                font.pixelSize: 18
                color: "#009900"
            }
        }

        RowLayout {
            spacing: 6;
            TextField {
                id: clientIP;
                implicitWidth: 150;
                placeholderText: qsTr("192.168.88.81");
                text: socketClient.ip
            }
            TextField {
                id: clientPort;
                implicitWidth: 160
                placeholderText: qsTr("8080");
                text: socketClient.port
            }
        }

        RowLayout {
            spacing: 6;
            CheckBox {
                id: autoConnect;
                text: qsTr("Auto connect");
                checked: socketClient.autoConnect;
                onClicked:
                {
                    socketClient.autoConnect = checked;
                }
            }
        }

        RowLayout {
            id: row19
            spacing: 5

            Text {
                id: statusText
                text: "Status: disconnected"
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#009900"
            }
        }

        RowLayout {
            spacing: 6;

            Button {
                implicitWidth: 100;
                text: "Connect";
                id: btnConnect;
                onClicked:
                {
                    socketClient.connectToServer(clientIP.text, clientPort.text);
                }
            }

            Button {
                implicitWidth: 100;
                text: "Disconnect";
                id: btnDisconnect;
                onClicked:
                {
                    socketClient.disconnectSocket();
                }
            }
        }
    }
}

