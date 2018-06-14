#include "IService.h"

IService::IService(QObject *parent) : QObject(parent)
{

}

void IService::setConfig(Config* config)
{
    this->config = config;
}

void IService::setLogger(Logger* value)
{
    this->logger = value;
}

void IService::log(const QString& value, Logger::LogType type)
{
    if(logger)
    {
        logger->log(value, type);
    }
}
