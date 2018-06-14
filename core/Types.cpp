#include "Types.h"
#include <QCoreApplication>

QString OneProcessData::getArgs()const
{
    return args;
}

QString OneProcessData::getMetaName() const
{
    return metaName;
}

QString OneProcessData::getFilePath() const
{
    return QCoreApplication::applicationDirPath() + "/" + filePath;
}

QString OneProcessData::getConfigPath() const
{
    return QCoreApplication::applicationDirPath() + "/" + configPath;
}

void OneProcessData::setArgs(const QString& value)
{
    args = value;
}

void OneProcessData::setMetaName(const QString& value)
{
    metaName = value;
}

void OneProcessData::setFilePath(const QString& value)
{
    filePath = value;
}

void OneProcessData::setConfigPath(const QString& value)
{
    configPath = value;
}

void OneProcessData::addCommand(const QString& metaName, const QString& action)
{
    CommandData command;
    command.metaName = metaName;
    command.action = action;
    commands.push_back(command);
}

QStringList OneProcessData::getCommandMetaNames()
{
    QStringList names;
    for(int j = 0; j < commands.size(); ++j)
    {
        names.push_back(commands[j].metaName);
    }

    return names;
}

QString OneProcessData::getCommandById(int id) const
{
    if(id < commands.length())
    {
        return commands[id].action;
    }

    return "";
}

void OneProcessData::setCommands(const QVector<CommandData>& value)
{
    commands = value;
}

QVector<CommandData> OneProcessData::getCommands() const
{
   return commands;
}

void OneProcessData::setSocketServer(const  SocketClientData& value)
{
    socketServer = value;
}

void OneProcessData::setConfigData(const  ProcessConfigData& value)
{
    processConfigData = value;
}

ProcessConfigData OneProcessData::getConfigData() const
{
    return processConfigData;
}
