#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <QObject>
#include <QQmlContext>
#include "mindwave/MindWave.h"
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

private:
     QQmlContext* qmlContext;
    // TCPSocketClient* client;
     SocketServerData socketServerData;
     QScopedPointer<MindWave>  mindWave;
     QScopedPointer<TCPSocketClient> client;
signals:

public slots:

private slots:
      void onItemDataRecieve(const QString& data);
};

#endif // CLIENTSERVICE_H
