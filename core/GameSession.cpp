#include "GameSession.h"
#include <QDateTime>
#include <QDebug>


GameSession::GameSession(QObject *parent) : QObject(parent)
{
    sessionTimer = new QTimer(this);
    connect(sessionTimer, SIGNAL(timeout()), this, SLOT(onSessionTimerUpdate()));
}

void GameSession::start()
{
    allTaskCleanTime = 0.;
    emit allTaskTimeChanged(allTaskCleanTime);

    sessionStartTime = QDateTime::currentMSecsSinceEpoch();
    sessionTimer->start(10);
}

void GameSession::stop()
{
     sessionTimer->stop();
}

void GameSession::addTaskTime(float time)
{
    allTaskCleanTime += time / 1000.;
    emit allTaskTimeChanged(allTaskCleanTime);
}

void GameSession::onSessionTimerUpdate()
{
    int newTime = QDateTime::currentMSecsSinceEpoch() - sessionStartTime;
    setSessionTime(newTime/ 1000.);
}

float GameSession::sessionTime() const
{
    return _sessionTime;
}

void GameSession::setSessionTime(float value)
{
    _sessionTime = value;
    emit sessionTimeChanged();
}
