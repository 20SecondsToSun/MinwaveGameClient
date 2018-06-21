#ifndef GAMETASKMANAGER_H
#define GAMETASKMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QVariantList>
#include "mindwave/MindWave.h"
#include "mindwave/GameTask.h"
#include "mindwave/GamePreTask.h"
#include "mindwave/TaskCreator.h"
#include "mindwave/GameSession.h"


class GameTaskManager: public QObject
{
    Q_OBJECT
public:
    GameTaskManager();

    Q_PROPERTY(float gameTime READ gameTime WRITE setGameTime NOTIFY gameTimeChanged)


    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE bool isRunning() const;
    Q_INVOKABLE bool isPreTaskState() const;

    Q_INVOKABLE QPointF getStartPoint() const;    
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE QPointF getEndPoint() const;
    Q_INVOKABLE QVariantList getCompletedPath() const;
    Q_INVOKABLE QVariantList getFullPath() const;
    Q_INVOKABLE float getForwardVectorRotation() const;
    Q_INVOKABLE float getAllTaskCleanTime() const;
    Q_INVOKABLE int getTaskCount() const;
    Q_INVOKABLE float getMindwaveLimit() const;

    void setMindWaveClient(MindWave* mindWave);

    float gameTime() const;
    void setGameTime(float value);

private:
    const int gameTimerMills = 10;
    const int preTaskMills = 3 * 1000;

    TaskCreator* taskCreator;


    QList<GameTask*> gameTasks;
    QList<GamePreTask*> gamePreTasks;
    GamePreTask* currentPreTask;
    GameTask* currentTask = nullptr;

    int currentTaskIndex = 0;
    MindWave* mindWave = nullptr;

    bool running = false;
    bool preTaskState = false;

    QTimer *gameTimer, *preTaskTimer;

    float _gameTime;
    float allTaskCleanTime;
    int gameStartTime, preTaskStartTime;

    void runTask();
    void preTaskTimerComplete();
    void setCurrentTaskIndex(int index);

    void initCurrentTask();

    GameSession* gameSession;

    bool isAllTaskCompleted() const;

signals:
    void updateCanvas();
    void gameTimeChanged();
    void taskComleteEvent(int taskNumber, int allTaskCount);
    void allTaskComleteEvent();

    void taskStartEvent();
    void preTaskStartEvent();
    void taskNumberChangedEvent(int taskNumber);
    void preTaskCoundownUpdate(float time);

private slots:
    void onGameTimerUpdate();
    //void onPreTaskTimerUpdate();
    void onTaskCompleteEvent();

private slots:
    void onPreGameTaskUpdate(float countDown);
    void onPreGameTaskComplete();
};

#endif // GAMETASKMANAGER_H
