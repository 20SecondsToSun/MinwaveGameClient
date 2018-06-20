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
    Q_INVOKABLE QPointF getStartPoint() const;
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE QVariantList getCompletedPath() const;
    Q_INVOKABLE QVariantList getFullPath() const;
    Q_INVOKABLE float getForwardVectorRotation() const;

    void setMindWaveClient(MindWave* mindWave);

    float gameTime() const;
    void setGameTime(float value);



private:
    QList<GameTask*> gameTasks;
    GameTask* currentTask = nullptr;

    int currentTaskIndex = 0;
    MindWave* mindWave = nullptr;
    bool running = false;
    QTimer *gameTimer;

    float _gameTime;
    int gameStartTime;


    const int gameTimerMills = 10;

    void runTask();

signals:
    void updateCanvas();
    void gameTimeChanged();
    void taskComleteEvent(int taskNumber, int allTaskCount);

private slots:
    void onGameTimerUpdate();
    void onTaskCompleteEvent();

};

#endif // GAMETASKMANAGER_H
