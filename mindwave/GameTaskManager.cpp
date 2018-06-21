#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{
    taskCreator = new TaskCreator();
    gameTasks = taskCreator->create();

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(onGameTimerUpdate()));    

    //preTasks = preTaskcreator->create();
    currentPreTask = new GamePreTask();
    connect(currentPreTask, SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    connect(currentPreTask, SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));

    gameSession = new GameSession();

    setGameTime(0);
}

void GameTaskManager::start()
{  
    setCurrentTaskIndex(0);

    gameSession->init();
    currentPreTask->init();
    currentPreTask->run();
    initCurrentTask();
    preTaskState = true;
    running = false;
    emit preTaskStartEvent();
}

void GameTaskManager::initCurrentTask()
{
    if(currentTask)
    {
        disconnect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    }
    currentTask = gameTasks.at(currentTaskIndex);
    connect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    currentTask->init();
}

void GameTaskManager::onPreGameTaskUpdate(float countDown)
{
    emit preTaskCoundownUpdate(countDown);
    emit updateCanvas();
}

void GameTaskManager::onPreGameTaskComplete()
{
    preTaskState = false;
    running = true;
    gameStartTime = QDateTime::currentMSecsSinceEpoch();

    currentTask->start();
    gameTimer->start(gameTimerMills);
    emit taskStartEvent();
}

void GameTaskManager::stop()
{
    running = false;
    preTaskState = false;
    currentTask->stop();
    gameTimer->stop();   
    allTaskCleanTime = 0;
    setGameTime(0);
    currentPreTask->stop();
    emit updateCanvas();
}

void GameTaskManager::onGameTimerUpdate()
{
    int newGameTime = QDateTime::currentMSecsSinceEpoch() - gameStartTime;
    setGameTime(allTaskCleanTime + newGameTime / 1000.0f);

    int humanValue = 0;
    if(mindWave)
    {
        humanValue = mindWave->attention();
    }
    currentTask->update(humanValue);

    emit updateCanvas();
}

void GameTaskManager::setCurrentTaskIndex(int index)
{
    currentTaskIndex = index;
    emit taskNumberChangedEvent(currentTaskIndex);
}

void GameTaskManager::onTaskCompleteEvent()
{
    qDebug()<<"-------------------------------onTaskCompleteEvent-------------------------------";

    auto completionTime = currentTask->getCompletionTime();
    gameSession->addTaskTime(completionTime);

    if(!isAllTaskCompleted())
    {
        setCurrentTaskIndex(currentTaskIndex + 1);
        emit taskComleteEvent(currentTaskIndex, gameTasks.length());
        gameTimer->stop();

        currentPreTask->init();
        currentPreTask->run();
        initCurrentTask();
        preTaskState = true;
        running = false;
        emit preTaskStartEvent();
    }
    else
    {
        emit taskComleteEvent(gameTasks.length(), gameTasks.length());
        emit allTaskComleteEvent();
        stop();
        qDebug()<<"------------------------------- Game Finished -------------------------------";
    }
}



bool GameTaskManager::isAllTaskCompleted() const
{
    return currentTaskIndex == gameTasks.length() - 1;
}

void GameTaskManager::setMindWaveClient(MindWave* value)
{
    mindWave = value;
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


bool GameTaskManager::isRunning() const
{
    return running;
}

bool GameTaskManager::isPreTaskState() const
{
    return preTaskState;
}


QPointF GameTaskManager::getStartPoint() const
{
   return currentTask->getStartPoint();
}

QPointF GameTaskManager::getCurPoint() const
{
   return currentTask->getCurPoint();
}

QPointF GameTaskManager::getEndPoint() const
{
   return currentTask->getEndPoint();
}

float GameTaskManager::getAllTaskCleanTime() const
{
   return allTaskCleanTime;
}

float GameTaskManager::getForwardVectorRotation() const
{
   return currentTask->getForwardVectorRotation();
}

QVariantList GameTaskManager::getCompletedPath() const
{
   return currentTask->getCompletedPath();
}

QVariantList GameTaskManager::getFullPath() const
{
   return currentTask->getFullPath();
}

int GameTaskManager::getTaskCount() const
{
    return gameTasks.length();
}

float GameTaskManager::getMindwaveLimit() const
{
    return currentTask->getMindwaveLimit();
}
