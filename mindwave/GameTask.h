#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QVector>
#include <QVector2D>

class GameTask
{
public:
    GameTask();
    GameTask(const QVector<QPointF>& value);
    void setPath(const QVector<QPointF>& value);

    void start();

    void update();
    void stop();

    QPointF getStartPoint() const;
    QPointF getCurPoint() const;

    void getCurrentPoint();
    QVector<QPointF> getCompletedPath() const;

private:
    QVector<QPointF> path;
    QPointF curPoint, startPoint, endPoint, position;
    int currentPointIndex = 0;
    bool taskComplete = false;
    QVector<QPointF> completedPath;
    QVector2D velocityDirection;

    void setPoints();

};

#endif // GAMETASK_H
