#include "BaseModule.h"

BaseModule::BaseModule()
{

}

void BaseModule::setConfig(Config* value)
{
    config = value;
}

void BaseModule:: setLogger(Logger* value)
{
    logger = value;
}
