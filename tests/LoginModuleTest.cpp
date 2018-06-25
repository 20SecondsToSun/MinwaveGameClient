#include "LoginModuleTest.h"

LoginModuleTest::LoginModuleTest():LoginModule()
{

}

void LoginModuleTest::setQmlContext(QQmlContext* qmlContext)
{
     qmlContext->setContextProperty("loginModule", this);
}

void LoginModuleTest::loginSuccessTest()
{
    emit loginStateChanged(LoginState::Success);
}
