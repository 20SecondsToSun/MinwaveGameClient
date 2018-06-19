#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{
    VelocityCalculator velocitycalculator;
    velocitycalculator.setLimits(0, 3, 60);

    QVector<QPointF> path;
    path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
    gameTasks.append(new GameTask(path, velocitycalculator));

    path.clear();
    path<<QPointF(100, 100)<<QPointF(200, 300)<<QPointF(200, 200)<<QPointF(200, 100);
    gameTasks.append(new GameTask(path, velocitycalculator));

    path.clear();
    path<<QPointF(500, 300)<<QPointF(800, 200)<<QPointF(900, 400)<<QPointF(500, 400);
    gameTasks.append(new GameTask(path, velocitycalculator));

    path.clear();
    path<<QPointF(200, 200)<<QPointF(200, 400)<<QPointF(500, 400)<<QPointF(500, 300);
    gameTasks.append(new GameTask(path, velocitycalculator));


    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(onGameTimerUpdate()));

    setGameTime(0);
}

void GameTaskManager::setMindWaveClient(MindWave* value)
{
    mindWave = value;
}

bool GameTaskManager::isRunning() const
{
    return running;
}

void GameTaskManager::setGameTime(float value)
{
    _gameTime = value;
    emit gameTimeChanged();
}

float GameTaskManager::gameTime() const
{
    return _gameTime;
}

void GameTaskManager::start()
{
    running = true;
    currentTaskIndex = 0;
    gameStartTime = QDateTime::currentMSecsSinceEpoch();
   // qDebug()<< QDateTime::currentMSecsSinceEpoch();
    runTask();
}

void GameTaskManager::runTask()
{
    if(currentTask)
    {
       disconnect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    }

    currentTask = gameTasks.at(currentTaskIndex);
    currentTask->start();
    connect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    gameTimer->start(gameTimerMills);
}

void GameTaskManager::stop()
{
    running = false;
    currentTask->stop();
    gameTimer->stop();
    emit updateCanvas();
}

void GameTaskManager::onGameTimerUpdate()
{
    int newGameTime = QDateTime::currentMSecsSinceEpoch() - gameStartTime;
    setGameTime(newGameTime / 1000.0f);


    int humanValue = 0;
    if(mindWave)
    {
        humanValue = mindWave->meditation();
    }
    currentTask->update(humanValue);

    emit updateCanvas();
}

QPointF GameTaskManager::getStartPoint() const
{
   return currentTask->getStartPoint();
}

QPointF GameTaskManager::getCurPoint() const
{
   return currentTask->getCurPoint();
}

void GameTaskManager::onTaskCompleteEvent()
{
     qDebug()<<"-------------------------------onTaskCompleteEvent-------------------------------";
    if(++currentTaskIndex < gameTasks.length())
    {
        emit taskComleteEvent(currentTaskIndex, gameTasks.length());
        runTask();
    }
    else
    {
        emit taskComleteEvent(gameTasks.length(), gameTasks.length());
        stop();
        qDebug()<<"------------------------------- Game Finished -------------------------------";
    }
}

QVariantList GameTaskManager::getCompletedPath() const
{
   return currentTask->getCompletedPath();
}

QVariantList GameTaskManager::getFullPath() const
{
   return currentTask->getFullPath();
}
