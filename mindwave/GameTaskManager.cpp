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
    QPointF point16 = QPointF(735, 465);
    QPointF point17 = QPointF(917, 495);
    QPointF point18 = QPointF(913, 570);
    QPointF point19 = QPointF(1144, 616);
    QPointF point20 = QPointF(1002, 316);


    //PATH0
   // path.clear();
   // path<<QPointF(200, 300)<<QPointF(400, 300)<<QPointF(600, 300)<<QPointF(600, 700);
   // gameTasks.append(new GameTask(path, velocitycalculator));



    //PATH1
    path.clear();
    path<<point4<<point6<<point10<<point7<<point16<<point17;
    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH2
//    path.clear();
//    path<<point17<<point20<<point3<<point2;
//    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH3
//    path.clear();
//    path<<point2<<point1<<point6<<point5<<point9;
//    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH4
//    path.clear();
//    path<<point9<<point13<<point10<<point14<<point15<<point16<<point17<<point18<<point19;
//    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH5
//    path.clear();
//    path<<point19<<point12<<point11<<point20<<point8<<point10<<point1;
//    gameTasks.append(new GameTask(path, velocitycalculator));

    // penta
    //path.clear();
    //path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
   // gameTasks.append(new GameTask(path, velocitycalculator));

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
