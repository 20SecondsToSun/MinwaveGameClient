#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <QObject>
#include <QQmlContext>
#include "components/MindwaveComponent.h"
#include "core/game/GameTaskManager.h"
#include <core/IService.h>

class TCPSocketClient;

class ClientService : public IService
{
    Q_OBJECT
public:
    explicit ClientService(QQmlContext* qmlContext, QObject *parent = nullptr);

    Q_INVOKABLE virtual void startService() override;
    virtual void setConfig(Config* config) override;
    virtual void stopService() override{};

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();

private:
     QQmlContext* qmlContext;
    // TCPSocketClient* client;
     SocketServerData socketServerData;
     QScopedPointer<MindwaveComponent>  mindWave;
     QScopedPointer<TCPSocketClient> client;
     QScopedPointer<GameTaskManager> gameTaskManager;
     QScopedPointer<GameSession> gameSession;

signals:

public slots:

private slots:
      void onItemDataRecieve(const QString& data);
      void onTaskComleteEvent(int currentTaskIndex, int completionTime, int allTaskCount);
};

#endif // CLIENTSERVICE_H
