#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    arduinoComponent = new ArduinoComponent();
    mindWaveComponent = new MindwaveComponent();
    healthCheckerComponent = new HealthCheckerComponent(arduinoComponent, mindWaveComponent);

    // loginModule = new LoginModule(arduinoComponent);
    // loginModule->setArduino(arduinoComponent);
    //  modules.append(loginModule);

    loginModule = new LoginModuleTest();
    loginModule->setArduino(arduinoComponent);
    modules.append(loginModule);

    instructionModule = new InstructionModule();
    modules.append(instructionModule);

    // gameModule = new GameModule(mindWaveComponent);
    // modules.append(gameModule);

    // resultModule = new ResultModule();
    // modules.append(resultModule);
}

void AppController::startInstruction()
{
    setAppState(AppState::Instruction);
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{
    for (auto module : modules)
    {
        module->setQmlContext(qmlContext);
    }
}

void AppController::setAppState(AppState value)
{
    if(currentModule)
    {
        currentModule->stop();
    }

    appState = value;

    currentModule = getModuleByAppState(value);

    currentModule->start();
    emit appStateChanged(value);
}

BaseModule* AppController::getModuleByAppState(AppState value)
{
    switch(value)
    {
    case AppState::Login: return loginModule;
    case AppState::Instruction: return instructionModule;
    }
}

void AppController::onConfigLoaded(Config* config)
{
    for (auto module : modules)
    {
        module->setConfig(config);
    }

    start();
}

void AppController::onConfigError()
{
    qDebug() << "config Service Error";
}

void AppController::setLogger(Logger* logger)
{
    for (auto module : modules)
    {
        module->setLogger(logger);
    }
}

void AppController::start()
{
    setAppState(AppState::Login);
}

