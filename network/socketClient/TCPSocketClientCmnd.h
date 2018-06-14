#ifndef TCPSOCKETCLIENTCMND_H
#define TCPSOCKETCLIENTCMND_H

#include "TCPSocketClient.h"
#include <QString>

class TCPSocketClientCmnd : public TCPSocketClient
{
     Q_OBJECT

public slots:
    virtual void readyRead() override;

public:
    TCPSocketClientCmnd();
    Q_INVOKABLE void sendCommand(int processId, const QString& command);

    virtual void setConfig(const SocketServerData& config) override;

private:
     QString initialResponse;
     QString initialCommand;
     QMap<QString, CommandType> commandMap;
};

#endif // TCPSOCKETCLIENTCMND_H
