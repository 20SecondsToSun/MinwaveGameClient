#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <QObject>
#include "config/Config.h"
#include "tools/Logger.h"

class BaseModule : public QObject
{
    Q_OBJECT
public:
    explicit BaseModule();

    virtual void setConfig(Config* config);
    virtual void setLogger(Logger* logger);
    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    Config* config;
    Logger* logger;

signals:

public slots:
};

#endif // BASEMODULE_H
