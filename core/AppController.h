#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QObject>
#include <QList>
#include "components/HealthCheckerComponent.h"
#include "components/ArduinoComponent.h"
#include "components/MindwaveComponent.h"
#include "StandInfo.h"
#include "tools/Logger.h"
#include "config/Config.h"
#include "LoginModule.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    enum class AppState
    {
        Login,
        Intstruction,
        Game,
        Result
    };
    Q_ENUMS(AppState)

public:
    explicit AppController(QObject *parent = nullptr);

public:   
    void setLogger(Logger* logger);
    void start();

private:
    LoginModule* loginModule;
    //InstructionModule instructionModule;
   // GameModule gameModule;
   // ResultModule resultModule;
    QList<BaseModule*> modules;

    HealthCheckerComponent* healthCheckerComponent;
    ArduinoComponent* arduinoComponent;
    MindwaveComponent* mindWaveComponent;

    StandInfo standInfo;
    Logger logger;
    Config* config;

    AppState appState = AppState::Login;
    BaseModule* currentModule = nullptr;

     void setAppState(AppState appState);

signals:
    void appStateChanged(AppState appState);

public slots:

    void onConfigLoaded(Config* config);
    void onConfigError();
};

#endif // APPCOPCONTROLLER_H
