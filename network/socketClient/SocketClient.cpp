#include "SocketClient.h"
#include <QDebug>

SocketClient::SocketClient()
{

}

bool SocketClient::connect(const QString &address, quint16 port)
{
    qDebug()<<"connect to client " <<address<<"  "<<port;
    return false;
}
