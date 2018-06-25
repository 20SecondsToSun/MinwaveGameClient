#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "components/ArduinoComponent.h"

class LoginModule : public BaseModule
{
    Q_OBJECT
public:
    enum class LoginState
    {
        Success,
        Error,
        UserDoesntExist,
        Undefined
    };
    Q_ENUMS(LoginState)

    LoginModule(QObject *parent = nullptr);

    void setArduino(ArduinoComponent* arduinoComponent);
    virtual void setConfig(Config* config) override;
    virtual void start() override;
    virtual void stop() override;

private:
    ArduinoComponent* arduinoComponent;   

signals:
    void loginStateChanged(LoginState loginState);


public slots:
};

#endif // LOGINMODULE_H
