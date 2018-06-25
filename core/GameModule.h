#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <QObject>
#include "BaseModule.h"

class GameModule : public BaseModule
{
    Q_OBJECT
public:
    GameModule();

    virtual void setConfig(Config* config) override;
    virtual void start() override;
    virtual void stop() override;

signals:

public slots:
};

#endif // GAMEMODULE_H
