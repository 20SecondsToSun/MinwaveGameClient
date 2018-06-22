#include "ClientService.h"
#include "network/socketClient/TCPSocketClient.h"

ClientService::ClientService(QQmlContext* qmlContext, QObject *parent) : IService(parent)
{
    this->qmlContext = qmlContext;
}

void ClientService::setConfig(Config* config)
{
    IService::setConfig(config);
    socketServerData = config->socketServerData;
}

void ClientService::startService()
{
   qDebug()<< this<<" startService ";

   if(!client)
   {
       client.reset(new TCPSocketClient);
       client->setConfig(socketServerData);
       //connect(server, SIGNAL(runningChanged()), this, SLOT(onRunningChanged()));
       //connect(server, SIGNAL(socketConnected(int)), this, SLOT(onItemConnected(int)));
       //connect(server, SIGNAL(socketDisconnected(int)), this, SLOT(onItemDisconnected(int)));
       connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
       qmlContext->setContextProperty("socketClient", client.data());
  }

  if(!mindWave)
  {
    mindWave.reset(new MindWave);
    qmlContext->setContextProperty("mind", mindWave.data());
  }

  if(!gameTaskManager)
  {
     gameTaskManager.reset(new GameTaskManager);
     gameTaskManager->setMindWaveClient(mindWave.data());
     qmlContext->setContextProperty("gameTaskManager", gameTaskManager.data());
     connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int, int, int)), this, SLOT(onTaskComleteEvent(int, int, int)));
  }

  if(client)
  {
      client->init();
  }

  if(!gameSession)
  {
     gameSession.reset(new GameSession());
     qmlContext->setContextProperty("gameSession", gameSession.data());
  }
}

void ClientService::onTaskComleteEvent(int currentTaskIndex, int completionTime, int allTaskCount)
{
    gameSession->addTaskTime(completionTime);
}

void ClientService::startGame()
{
    gameSession->start();
    gameTaskManager->start();
}

void ClientService::stopGame()
{
     gameTaskManager->stop();
     gameSession->stop();
}

void ClientService::onItemDataRecieve(const QString& data)
{
    QStringList json = data.split('\r');
    int count = 0;
   // qDebug()<<"--------------------------------";
    for(int i = 0; i < json.length(); i++)
    {
        if(json[i].indexOf("eSense") != -1)
        {
            count++;
            mindWave->parse(json[i]);
            break;
        }
    }
    // qDebug()<<count;
    // qDebug()<<"--------------------------------";
}

