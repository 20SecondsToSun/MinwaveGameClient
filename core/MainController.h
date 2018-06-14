#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <core/IService.h>

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    void addService(IService* service);
    void setLogger(Logger* value);

public slots:
    void configServiceReady(Config* config);
    void configServiceError();

private:
    QList<IService*> services;
};

#endif // MAINCONTROLLER_H
