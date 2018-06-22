#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>

typedef int LancherId;
typedef QVector<class OneProcessData> ProcessData;

enum class AppTypeId
{
    Undefined,
    Installation,
    Mobile,
    Launcher,
    ServerApp,
    ServerWeb
};

enum class CommandType
{
    None,
    ClientAuth,
    KeepAliveToggle,
    GetInfo
};

enum class UpdateProviderType
{
    Undefined,
    RemoteFolder,
    Server,
    FTP
};

struct Command
{
    QString metaName;
    QString action;
};

struct CommandData
{
    QString metaName;
    QString action;
};

struct ConfigData
{
    QString version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int launcherId;
    AppTypeId appTypeId;
    bool runInMiniimalSize;
};

struct SocketServerData
{
    QString ip = "192.168.88.97";
    int port = 8000;
    bool autoConnect = true;
    QString delimeter;
    QString initialCommand;
    QList<AppTypeId> connectionTypesAllow;
};

struct SocketClientData
{
    QString ip = "192.168.88.89";
    int port = 8080;
    bool autoConnect = true;
    QString delimeter;
};

struct ProcessConfigData
{
    QString version;
    QString logPath;
    AppTypeId appTypeId;
    int appId;
    int installationId;
    QJsonObject rawConfig;
};

class OneProcessData
{
public:
    QString getArgs()const;
    QString getMetaName() const;
    QString getFilePath() const;
    QString getConfigPath() const;
    QVector<CommandData> getCommands() const;

    void setArgs(const QString& value);
    void setMetaName(const QString& value);
    void setFilePath(const QString& value);
    void setConfigPath(const QString& value);
    void setCommands(const  QVector<CommandData>& value);
    void setSocketServer(const  SocketClientData& value);
    void setConfigData(const  ProcessConfigData& value);
    void addCommand(const QString& metaName, const QString& action);

    QStringList getCommandMetaNames();
    QString getCommandById(int id) const;
    ProcessConfigData getConfigData() const;

private:
    QString args;
    QString metaName;
    QString filePath;
    QString configPath;   
    QString configVersion;
    AppTypeId appId;
    SocketClientData socketServer;
    ProcessConfigData processConfigData;
    QVector<CommandData> commands;
};

struct MonitoringData
{
    bool enabled;
};

struct AutoUpdateProviderData
{
    float checkUpdateMilliseconds;
    QString path;
};

struct AutoUpdateData
{
    bool enabled;
    UpdateProviderType providerType;
    QMap<UpdateProviderType, AutoUpdateProviderData> providersData;

   AutoUpdateProviderData getProviderData() const
   {
       return providersData[providerType];
   }
};


struct ConnectedAppData
{
    AppTypeId appTypeId;
    int appId;

    QString getLogInfo() const
    {
        return "app type id " + QString::number((int)appTypeId) + " app id " + QString::number(appId);
    }
};

struct ConnectedClientTypeMetaData
{
    ConnectedClientTypeMetaData()
    {

    }

    ConnectedClientTypeMetaData(AppTypeId type)
    {
        count = 0;
        color = "black";
        switch(type)
        {
        case AppTypeId::Undefined:
            metaName = "undefined";
            color = "red";
            break;
        case AppTypeId::Installation:
            metaName = "installations";
            break;
        case AppTypeId::Mobile:
            metaName = "mobile";
            break;
        case AppTypeId::Launcher:
            metaName = "launcher";
            break;
        case AppTypeId::ServerApp:
            metaName = "serverApp";
            break;
        case AppTypeId::ServerWeb:
            metaName = "serverWeb";
            break;
        }
    }

    int count;
    QString color;
    QString metaName;

    QString getFormatString(int connectionsNum) const
    {
       QString colorOut = connectionsNum > 0 ? "green" : color;
       return  "<font color=" + colorOut + ">" + metaName + ":" + QString::number(connectionsNum) + "</font>";
    }
};

#endif // TYPES_H
