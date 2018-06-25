#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug.h>

ConfigParser::ConfigParser()
{
    config = new Config();
}

void ConfigParser::parse(const QString& configData)
{
    try
    {
        //qDebug()<<"configData................"<<endl;
       // qDebug()<<configData <<endl;
       // qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        config->configData = parseConfigData(jsonObj);
        //config->processData = parseProcessesData(jsonObj);
       // config->socketServerData = parseSocketServerData(jsonObj);
       // config->socketClientData = parseSocketClientData(jsonObj);
      // config->monitoringData = parseMonitoringData(jsonObj);
       // config->autoUpdateData = parseAutoUpdateData(jsonObj);
        config->setRawData(configData);
        config->valid = true;
        emit parseComplete(config);
    }
    catch(...)
    {
        config->valid = false;
        qDebug()<<"parsing error................";
    }
}

ConfigData ConfigParser::parseConfigData(const QJsonObject& jsonObj)
{
    ConfigData configData;
    configData.version = jsonObj["version"].toString();
    configData.configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    configData.needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    configData.launcherId = jsonObj["launcherId"].toInt();
    configData.appTypeId = AppTypeId(jsonObj["appTypeId"].toInt());
    configData.runInMiniimalSize = jsonObj["runInMiniimalSize"].toBool();
    return configData;
}

QVector<OneProcessData> ConfigParser::parseProcessesData(const QJsonObject& jsonObj)
{
    QJsonArray processesJson = jsonObj["processes"].toArray();
    QVector<OneProcessData> processes;
    for(int j = 0; j < processesJson.size(); ++j)
    {
        QJsonObject processJson = processesJson[j].toObject();

        OneProcessData process;
        process.setArgs(processJson.value("args").toString());
        process.setMetaName(processJson.value("metaName").toString());
        process.setFilePath(processJson.value("filePath").toString());
        QString configPath = processJson.value("configPath").toString();
        process.setConfigPath(configPath);

        QJsonObject prConfJsonObj   = processJson.value("config").toObject();
        process.setCommands(parseProcessCommandData(prConfJsonObj));
        process.setSocketServer(parseSocketClientData(prConfJsonObj));
        process.setConfigData(parseProcessConfigData(prConfJsonObj));

        processes.push_back(process);
    }

    return processes;
}

SocketServerData ConfigParser::parseSocketServerData(const QJsonObject& jsonObj)
{
    SocketServerData socketServerData;
    QJsonObject serverJson = jsonObj["socketServer"].toObject();
    socketServerData.ip = serverJson.value("ip").toString();
    if(socketServerData.ip == "localhost")
    {

    }
    socketServerData.port = serverJson.value("port").toInt();
    socketServerData.autoConnect = serverJson.value("autoConnect").toBool();
    socketServerData.delimeter = serverJson.value("delimeter").toString();
    socketServerData.initialCommand = serverJson.value("initialCommand").toString();
    QJsonArray connectionTypesAllowJson = serverJson["connectionTypesAllow"].toArray();
    QList<AppTypeId> types;
    for(int j = 0; j < connectionTypesAllowJson.size(); ++j)
    {
        AppTypeId type = AppTypeId(connectionTypesAllowJson[j].toInt());
        types.push_back(type);
    }
    socketServerData.connectionTypesAllow = types;

    return socketServerData;
}

SocketClientData ConfigParser::parseSocketClientData(const QJsonObject& jsonObj)
{
    SocketClientData socketClientData;
    QJsonObject clientJson = jsonObj["socketClient"].toObject();
    socketClientData.ip = clientJson.value("ip").toString();
    socketClientData.port = clientJson.value("port").toInt();
    socketClientData.autoConnect = clientJson.value("autoConnect").toBool();
    socketClientData.delimeter = clientJson.value("delimeter").toString();
    return socketClientData;
}

MonitoringData ConfigParser::parseMonitoringData(const QJsonObject& jsonObj)
{
    MonitoringData monitoringData;
    QJsonObject monitoringJson = jsonObj["monitoring"].toObject();
    monitoringData.enabled = monitoringJson.value("enabled").toBool();
    return monitoringData;
}


QVector<CommandData> ConfigParser::parseProcessCommandData(const QJsonObject& jsonObj)
{
    QVector<CommandData> processCommandData;

    QJsonArray commandsJson = jsonObj.value("commands").toArray();
    for(int j = 0; j < commandsJson.size(); ++j)
    {
        QJsonObject commandObject = commandsJson[j].toObject();
        CommandData cData;
        cData.action = commandObject.value("action").toString();
        cData.metaName = commandObject.value("metaName").toString();
        processCommandData.push_back(cData);
    }

    return processCommandData;
}

ProcessConfigData ConfigParser::parseProcessConfigData(const QJsonObject& jsonObj)
{
    ProcessConfigData processConfigData;
    processConfigData.appTypeId = AppTypeId(jsonObj.value("appTypeId").toInt());
    processConfigData.appId = jsonObj.value("appId").toInt();
    processConfigData.installationId = jsonObj.value("installationId").toInt();
    processConfigData.version = jsonObj.value("version").toString();
    processConfigData.logPath = jsonObj.value("logPath").toString();
    processConfigData.rawConfig = jsonObj;

    return processConfigData;
}

AutoUpdateData ConfigParser::parseAutoUpdateData(const QJsonObject& jsonObj)
{
    AutoUpdateData autoUpdateData;
    QJsonObject autoUpdateJson = jsonObj["autoUpdate"].toObject();
    autoUpdateData.providerType = UpdateProviderType(autoUpdateJson.value("provider").toInt());
    autoUpdateData.enabled = autoUpdateJson.value("enabled").toBool();

    auto remoteFolderJson = autoUpdateJson.value("remoteFolder").toObject();
    AutoUpdateProviderData remoteFolderProviderData;
    remoteFolderProviderData.checkUpdateMilliseconds = remoteFolderJson.value("checkUpdateMilliseconds").toDouble();
    remoteFolderProviderData.path = remoteFolderJson.value("path").toString();
    autoUpdateData.providersData.insert(UpdateProviderType::RemoteFolder, remoteFolderProviderData);
    return autoUpdateData;
}
