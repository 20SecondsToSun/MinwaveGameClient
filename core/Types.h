#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>

typedef int StandId;

struct TCPConfig
{
    QString ip = "127.0.0.1";
    int port = 13854;
    bool autoConnect = true;
    QString delimeter = "\r";
};

struct MindwaveConfig
{
   TCPConfig tcpConfig;
};

struct ConfigData
{
    QString version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    StandId launcherId;
};


#endif // TYPES_H
