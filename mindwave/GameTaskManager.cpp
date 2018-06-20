#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{
    VelocityCalculator velocitycalculator;
    velocitycalculator.setLimits(0, 3, 60);

    QVector<QPointF> path;
    QPointF point1 = QPointF(388, 88);
    QPointF point2 = QPointF(621, 71 );
    QPointF point3 = QPointF(970, 114);
    QPointF point4 = QPointF(223, 222);
    QPointF point5 = QPointF(347, 243);
    QPointF point6 = QPointF(467, 264);
    QPointF point7 = QPointF(690, 300);
    QPointF point8 = QPointF(987, 207);
    QPointF point9 = QPointF(218, 422);
    QPointF point10 = QPointF(511, 357);
    QPointF point11 = QPointF(969, 389);
    QPointF point12 = QPointF(1152, 379);
    QPointF point13 = QPointF(315, 537);
    QPointF point14 = QPointF(573, 417);
    QPointF point15 = QPointF(666, 500);
    QPointF point16 = QPointF(735, 458);
    QPointF point17 = QPointF(917, 495);
    QPointF point18 = QPointF(913, 570);
    QPointF point19 = QPointF(1144, 616);
    QPointF point20 = QPointF(1002, 316);

    //PATH1
    path.clear();
    path<<point4<<point6<<point10<<point7<<point16<<point17;
    velocitycalculator.setLimits(0, 3.5, 40);
    gameTasks.append(new GameTask(path, velocitycalculator));

    //PATH2
    path.clear();
    path<<point17<<point20<<point3<<point2;
    velocitycalculator.setLimits(0, 3.3, 45);
    gameTasks.append(new GameTask(path, velocitycalculator));

    //PATH3
    path.clear();
    velocitycalculator.setLimits(0, 3, 60);
    path<<point2<<point1<<point6<<point5<<point9;
    gameTasks.append(new GameTask(path, velocitycalculator));

    //PATH4
    path.clear();
    velocitycalculator.setLimits(0, 2, 65);
    path<<point9<<point13<<point10<<point14<<point15<<point16<<point17<<point18<<point19;
    gameTasks.append(new GameTask(path, velocitycalculator));

    //PATH5
    path.clear();
    velocitycalculator.setLimits(0, 3, 70);
    path<<point19<<point12<<point11<<point20<<point8<<point10<<point1;
    gameTasks.append(new GameTask(path, velocitycalculator));

    //penta
    //path.clear();
    //path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
    //gameTasks.append(new GameTask(path, velocitycalculator));

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(onGameTimerUpdate()));

    preTaskTimer = new QTimer(this);
    connect(preTaskTimer, SIGNAL(timeout()), this, SLOT(onPreTaskTimerUpdate()));

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

bool GameTaskManager::isPreTaskState() const
{
    return preTaskState;
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
    setCurrentTaskIndex(0);
    allTaskCleanTime = 0;
    runPreTask();
}

void GameTaskManager::runPreTask()
{
    if(currentTask)
    {
        disconnect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    }
    currentTask = gameTasks.at(currentTaskIndex);
    currentTask->init();

    preTaskStartTime = QDateTime::currentMSecsSinceEpoch();
    preTaskTimer->start(10);
    preTaskState = true;

    running = false;
    emit preTaskStartEvent();
}

void GameTaskManager::onPreTaskTimerUpdate()
{
    int newPreGameTime = QDateTime::currentMSecsSinceEpoch() - preTaskStartTime;
    emit preTaskCoundownUpdate((preTaskMills - newPreGameTime) / 1000.0f);

    if(newPreGameTime < preTaskMills)
    {
         emit updateCanvas();
    }
    else
    {
        preTaskTimer->stop();
        preTaskTimerComplete();
    }
}

void GameTaskManager::preTaskTimerComplete()
{
    preTaskState = false;
    running = true;
    gameStartTime = QDateTime::currentMSecsSinceEpoch();
    runTask();
}

void GameTaskManager::runTask()
{   
    currentTask->start();
    connect(currentTask, SIGNAL(taskCompleteEvent()), this, SLOT(onTaskCompleteEvent()));
    gameTimer->start(gameTimerMills);
    emit taskStartEvent();
}

void GameTaskManager::stop()
{
    running = false;
    preTaskState = false;
    currentTask->stop();
    gameTimer->stop();
    preTaskTimer->stop();
    allTaskCleanTime = 0;
    setGameTime(0);
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

    allTaskCleanTime += currentTask->getCompletionTime() / 1000.;

    if(currentTaskIndex + 1 < gameTasks.length())
    {
        setCurrentTaskIndex(currentTaskIndex + 1);
        emit taskComleteEvent(currentTaskIndex, gameTasks.length());
        gameTimer->stop();
        runPreTask();
    }
    else
    {
        emit taskComleteEvent(gameTasks.length(), gameTasks.length());
        emit allTaskComleteEvent();
        stop();

        qDebug()<<"------------------------------- Game Finished -------------------------------";
    }
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
