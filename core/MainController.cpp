#include "MainController.h"
#include <QDebug>

MainController::MainController(QObject *parent) : QObject(parent)
{

}

void MainController::configServiceReady(Config* config)
{
    for (auto service : services)
    {
        service->setConfig(config);
        service->startService();
    }
}

void MainController::configServiceError()
{
    qDebug() << "config Service Error";
}

void MainController::addService(IService* service)
{
    services.push_back(service);
}

void MainController::setLogger(Logger* value)
{
    for (auto service : services)
    {
         service->setLogger(value);
    }
}
