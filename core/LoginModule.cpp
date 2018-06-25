#include "LoginModule.h"

LoginModule::LoginModule(ArduinoComponent* value):BaseModule()
{
    arduinoComponent = value;
}

void LoginModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
   // socketServerData = config->socketServerData;
}

void LoginModule::start()
{

}

void LoginModule::stop()
{

}
