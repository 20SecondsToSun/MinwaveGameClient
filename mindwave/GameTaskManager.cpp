#include "GameTaskManager.h"
#include <QDebug>

GameTaskManager::GameTaskManager()
{
    QVector<QPointF> path;
    path<<QPointF(100, 100)<<QPointF(100, 200)<<QPointF(200, 200)<<QPointF(200, 300);
    gameTasks.append(GameTask(path));
    gameTasks.append(GameTask(path));
    gameTasks.append(GameTask(path));

    currentTask = gameTasks.at(currentTaskIndex);

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(onGameTimerUpdate()));
}

void GameTaskManager::setMindWaveClient(MindWave* value)
{
    mindWave = value;
}

bool GameTaskManager::isRunning() const
{
    return running;
}

void GameTaskManager::start()
{
    running = true;
    currentTask.start();
    gameTimer->start(gameTimerMills);
}

void GameTaskManager::stop()
{
    running = false;
    currentTask.stop();
    gameTimer->stop();
}

void GameTaskManager::onGameTimerUpdate()
{
    currentTask.update();
    emit updateCanvas();
}

QPointF GameTaskManager::getStartPoint() const
{
   return currentTask.getStartPoint();
}

QPointF GameTaskManager::getCurPoint() const
{
   return currentTask.getCurPoint();
}


QVariantList GameTaskManager::getCompletedPath() const
{
    QVariantList list;
    auto completedPath = currentTask.getCompletedPath();
    for(int i = 0; i< completedPath.length(); i++)
    {
        list.append(completedPath[i]);
    }
   return list;//currentTask.getCompletedPath();
}
