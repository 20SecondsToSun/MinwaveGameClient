#include "GameModule.h"

GameModule::GameModule() : BaseModule()
{
    client.reset(new TCPSocketClient);
    client->setConfig(socketServerData);
    connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    client->init();

    mindWave.reset(new MindwaveComponent);
    qmlContext->setContextProperty("mind", mindWave.data());

    gameTaskManager.reset(new GameTaskManager);
    gameTaskManager->setMindWaveClient(mindWave.data());
    connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int, int, int)), this, SLOT(onTaskComleteEvent(int, int, int)));

    gameSession.reset(new GameSession());
}

void GameModule::setQmlContext(QQmlContext* value)
{
    BaseModule::setQmlContext(value);

    qmlContext->setContextProperty("socketClient", client.data());
    qmlContext->setContextProperty("gameTaskManager", gameTaskManager.data());
    qmlContext->setContextProperty("gameSession", gameSession.data());
}

void GameModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
    // socketServerData = config->socketServerData;
}

void GameModule::start()
{
    qDebug()<< this<<" startService ";
}

void GameModule::stop()
{

}


void GameModule::onTaskComleteEvent(int currentTaskIndex, int completionTime, int allTaskCount)
{
    gameSession->addTaskTime(completionTime);
}

void GameModule::startGame()
{
    gameSession->start();
    gameTaskManager->start();
}

void GameModule::stopGame()
{
    gameTaskManager->stop();
    gameSession->stop();
}

void GameModule::onItemDataRecieve(const QString& data)
{
    QStringList json = data.split('\r');
    int count = 0;

    for(int i = 0; i < json.length(); i++)
    {
        if(json[i].indexOf("eSense") != -1)
        {
            count++;
            mindWave->parse(json[i]);
            break;
        }
    }
}
