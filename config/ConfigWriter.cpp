#include "ConfigWriter.h"
#include "ConfigLoader.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

ConfigWriter::ConfigWriter()
{

}

void ConfigWriter::save(Config* config, const QString& path)
{
    qDebug()<<"update local config to "<< path;
    QJsonDocument doc = QJsonDocument::fromJson(config->getRawData().toUtf8());

    QFile saveFile(path);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }
    else
    {
        saveFile.write(doc.toJson());
    }
}

void ConfigWriter::saveProcessConfigData(Config* config, int processId)
{
    if(config)
    {
        OneProcessData processData = config->processData[processId];
        auto path = processData.getConfigPath();
        ConfigLoader loader;
        loader.load(ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE, path);

        QJsonObject configObject;

//        if(loader.isValid())
//        {
//            QString processConfig = loader.getConfig();
//            qDebug()<<"work with existing config for installation ";

//            QJsonDocument jsonDoc = QJsonDocument::fromJson(processConfig.toUtf8());
//            configObject = jsonDoc.object();

//            auto processConfigData = processData.getConfigData();
//            configObject["version"] = QJsonValue::fromVariant(processConfigData.version);
//            configObject["appTypeId"] = QJsonValue::fromVariant(int(processConfigData.appTypeId));
//            configObject["appId"] = QJsonValue::fromVariant(processConfigData.appId);
//            configObject["logPath"] = QJsonValue::fromVariant(processConfigData.logPath);

//            auto serverData = config->socketServerData;
//            QJsonObject socketClientObject = configObject["socketServer"].toObject();
//            socketClientObject["ip"] = QJsonValue::fromVariant(serverData.ip);
//            socketClientObject["port"] = QJsonValue::fromVariant(serverData.port);
//            socketClientObject["autoConnect"] = QJsonValue::fromVariant(serverData.autoConnect);
//            socketClientObject["delimeter"] = QJsonValue::fromVariant(serverData.delimeter);
//            configObject["socketServer"] = socketClientObject;

//            QJsonArray commandsArray;
//            auto commands = processData.getCommands();

//            for(CommandData command : commands)
//            {
//                QJsonObject commandObject;
//                commandObject.insert("action", QJsonValue::fromVariant(command.action));
//                commandObject.insert("metaName", QJsonValue::fromVariant(command.metaName));
//                commandsArray.push_back(commandObject);
//            }
//            configObject["commands"] = commandsArray;
//        }
//        else
//        {
            auto processConfigData = processData.getConfigData();
            configObject = processConfigData.rawConfig;

           // configObject.insert("version", QJsonValue::fromVariant(processConfigData.version));
           // configObject.insert("appTypeId", QJsonValue::fromVariant(int(processConfigData.appTypeId)));
           // configObject.insert("appId", QJsonValue::fromVariant(processConfigData.appId));
           // configObject.insert("logPath", QJsonValue::fromVariant(processConfigData.logPath));

            auto serverData = config->socketServerData;
            QJsonObject socketClientObject;
            socketClientObject.insert("ip", QJsonValue::fromVariant(serverData.ip));
            socketClientObject.insert("port", QJsonValue::fromVariant(serverData.port));
            socketClientObject.insert("autoConnect", QJsonValue::fromVariant(serverData.autoConnect));
            socketClientObject.insert("delimeter", QJsonValue::fromVariant(serverData.delimeter));
            configObject["socketServer"] = socketClientObject;

            configObject["logPath"] = QJsonValue::fromVariant(processConfigData.logPath);
           // configObject.insert("socketServer", socketClientObject);

//            QJsonArray commandsArray;
//            auto commands = processData.getCommands();

//            for(CommandData command : commands)
//            {
//                QJsonObject commandObject;
//                commandObject.insert("action", QJsonValue::fromVariant(command.action));
//                commandObject.insert("metaName", QJsonValue::fromVariant(command.metaName));
//                commandsArray.push_back(commandObject);
//            }
//            configObject.insert("commands", commandsArray);
       // }

        QJsonDocument doc(configObject);
        QFile saveFile(path);

        if (!saveFile.open(QIODevice::WriteOnly))
        {
            qWarning("Couldn't open save file.");
        }
        else
        {           
            saveFile.write(doc.toJson());
        }
    }
    else
    {
        //error
    }
}
