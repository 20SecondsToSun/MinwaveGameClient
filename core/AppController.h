#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QQmlContext>
#include <QObject>
#include <QList>
#include "components/HealthCheckerComponent.h"
#include "components/ArduinoComponent.h"
#include "components/MindwaveComponent.h"
#include "StandInfo.h"
#include "tools/Logger.h"
#include "config/Config.h"
#include "LoginModule.h"
#include "InstructionModule.h"

#include "tests/LoginModuleTest.h"
#include "Types.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    enum class AppState
    {
        Login,
        Instruction,
        Game,
        Result
    };
    Q_ENUMS(AppState)

    AppController(QObject *parent = nullptr);

public:   
    void setLogger(Logger* logger);
    void start();
    void setQmlContext(QQmlContext* qmlContext);

    Q_INVOKABLE void startInstruction();


private:
    LoginModule* loginModule;
    LoginModuleTest* loginModuleTest;
    InstructionModule* instructionModule;
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
    BaseModule* getModuleByAppState(AppState value);

signals:
    void appStateChanged(AppState appState);

public slots:

    void onConfigLoaded(Config* config);
    void onConfigError();
};

#endif // APPCOPCONTROLLER_H
