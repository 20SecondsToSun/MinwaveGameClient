#include "TCPSocketClientCmnd.h"

TCPSocketClientCmnd::TCPSocketClientCmnd()
{
    commandMap.insert("clientAuth", CommandType::ClientAuth);
}

void TCPSocketClientCmnd::readyRead()
{
    QByteArray data = socket->readAll();
    QString  s_data = getLastMessage(data);
    qDebug()<< this << "data = " <<s_data;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(s_data.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QJsonObject response = jsonObject.value("command").toObject();
    QString type = response.value("type").toString();

    qDebug()<<"type "<< type;

     switch(commandMap.value(type))
    {
        case CommandType::ClientAuth:
        {
            sendData(initialResponse);
        }
    }
}

void TCPSocketClientCmnd::setConfig(const SocketServerData& config)
{
    initialCommand = config.initialCommand;
   // initialResponse = config.initialResponse;
    TCPSocketClient::setConfig(config);
}

void TCPSocketClientCmnd::sendCommand(int processId, const QString& command)
{
   auto commandTest = "{\"command\":{\"type\":\"nextArt\"}}[/TCP]";

   qDebug()<<"TCPSocketClientCmnd::command "<< command;
   sendData(commandTest);
}
