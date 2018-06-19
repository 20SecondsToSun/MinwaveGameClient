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

    void setMindWaveClient(MindWave* mindWave);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE bool isRunning() const;
    Q_INVOKABLE QPointF getStartPoint() const;
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE QVariantList getCompletedPath() const;

private:
    QList<GameTask> gameTasks;
    GameTask currentTask;

    int currentTaskIndex = 0;
    MindWave* mindWave = nullptr;
    bool running = false;
    QTimer *gameTimer;

    const int gameTimerMills = 10;

signals:
    void updateCanvas();

private slots:
    void onGameTimerUpdate();

};

#endif // GAMETASKMANAGER_H
