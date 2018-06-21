#include "GameSession.h"

GameSession::GameSession(QObject *parent) : QObject(parent)
{

}

void GameSession::init()
{
    allTaskCleanTime = 0;
}

void GameSession::addTaskTime(float time)
{
    allTaskCleanTime += time / 1000.;

}


