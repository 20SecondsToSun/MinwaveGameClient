#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QObject>
#include <QString>
#include "Config.h"

class ConfigParser : public QObject
{
    Q_OBJECT

public:
    ConfigParser();

signals:
    void parseComplete(Config* );
    void parseError();

public slots:
    void parse(const QString& configData);

private:
    Config* config;

    ConfigData parseConfigData(const QJsonObject& jsonObj);
    QVector<OneProcessData> parseProcessesData(const QJsonObject& jsonObj);
    SocketServerData parseSocketServerData(const QJsonObject& jsonObj);
    SocketClientData parseSocketClientData(const QJsonObject& jsonObj);
    MonitoringData parseMonitoringData(const QJsonObject& jsonObj);    
    QVector<CommandData> parseProcessCommandData(const QJsonObject& jsonObj);
    ProcessConfigData parseProcessConfigData(const QJsonObject& jsonObj);
    AutoUpdateData parseAutoUpdateData(const QJsonObject& jsonObj);

};

#endif // CONFIGPARSER_H
