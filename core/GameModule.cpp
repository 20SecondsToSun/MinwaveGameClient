#include "GameModule.h"

GameModule::GameModule() : BaseModule()
{
   mindWave.reset(new MindwaveComponent);

   gameTaskManager.reset(new GameTaskManager);
   gameTaskManager->setMindWaveClient(mindWave.data());
   connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int, int, int)), this, SLOT(onTaskComleteEvent(int, int, int)));

   gameSession.reset(new GameSession());
}

void GameModule::setQmlContext(QQmlContext* value)
{
    BaseModule::setQmlContext(value);

    qmlContext->setContextProperty("mind", mindWave.data());   
    qmlContext->setContextProperty("gameTaskManager", gameTaskManager.data());
    qmlContext->setContextProperty("gameSession", gameSession.data());
}

void GameModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
    mindWave->setConfig(config->mindwaveConfig);
}

void GameModule::start()
{
    gameSession->start();
    gameTaskManager->start();
}

void GameModule::stop()
{
    gameTaskManager->stop();
     gameSession->stop();
}

void GameModule::onTaskComleteEvent(int currentTaskIndex, int completionTime, int allTaskCount)
{
    gameSession->addTaskTime(completionTime);
}
