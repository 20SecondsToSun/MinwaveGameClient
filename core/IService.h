#ifndef ISERVICE_H
#define ISERVICE_H

#include <QObject>
#include "config/Config.h"
#include "tools/Logger.h"

class IService : public QObject
{
    Q_OBJECT
public:
    explicit IService(QObject *parent = nullptr);

    virtual void setConfig(Config* config);

    virtual void setProvider()  {};
    virtual void startService() = 0;
    virtual void stopService()  = 0;

   void virtual setLogger(Logger* value);

protected:
    void log(const QString& value, Logger::LogType type = Logger::LogType::Verbose);

private:
    Config* config;
    Logger* logger = nullptr;
};

#endif // ISERVICE_H
