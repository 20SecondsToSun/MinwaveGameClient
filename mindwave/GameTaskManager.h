#ifndef GAMETASKMANAGER_H
#define GAMETASKMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QVariantList>
#include "mindwave/MindWave.h"
#include "mindwave/GameTask.h"

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
    Q_INVOKABLE QVariantList getCompletedPath() const;
    Q_INVOKABLE QVariantList getFullPath() const;
    Q_INVOKABLE float getForwardVectorRotation() const;
    Q_INVOKABLE int getTaskCount() const;

    void setMindWaveClient(MindWave* mindWave);

    float gameTime() const;
    void setGameTime(float value);

private:
    QList<GameTask*> gameTasks;
    GameTask* currentTask = nullptr;

    int currentTaskIndex = 0;
    MindWave* mindWave = nullptr;

    bool running = false;
    bool preTaskState = false;

    QTimer *gameTimer, *preTaskTimer;

    float _gameTime;
    float allTaskCleanTime;
    int gameStartTime, preTaskStartTime;


    const int gameTimerMills = 10;
    const int preTaskMills = 2 * 1000;

   // QMetaObject::Connection taskCompleteSignal;

    void runPreTask();
    void runTask();
    void preTaskTimerComplete();

signals:
    void updateCanvas();
    void gameTimeChanged();
    void taskComleteEvent(int taskNumber, int allTaskCount);
    void allTaskComleteEvent();

private slots:
    void onGameTimerUpdate();

    void onPreTaskTimerUpdate();
    void onTaskCompleteEvent();

};

#endif // GAMETASKMANAGER_H
