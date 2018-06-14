#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>

class SocketClient: public QObject
{
    Q_OBJECT

public:
    SocketClient();
    Q_INVOKABLE bool connect(const QString& address, quint16 port);

};

#endif // SOCKETCLIENT_H
