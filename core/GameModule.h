#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "components/MindwaveComponent.h"
#include "core/game/GameTaskManager.h"
#include "network/socketClient/TCPSocketClient.h"

class GameModule : public BaseModule
{
    Q_OBJECT
public:
    GameModule();

    virtual void setConfig(Config* config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setQmlContext(QQmlContext* value) override;

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();

private:
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

#endif // GAMEMODULE_H
