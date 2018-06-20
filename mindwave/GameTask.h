#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QVector>
#include <QVector2D>
#include "mindwave/VelocityCalculator.h"

class GameTask: public QObject
{
    Q_OBJECT

public:
    GameTask();
    GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc);
    void setPath(const QVector<QPointF>& value);

    void init();
    void start();
    void stop();

    void update(int humanValue);    

    QPointF getStartPoint() const;    
    QPointF getCurPoint() const;
    QPointF getEndPoint() const;
    int getCompletionTime() const;

    void getCurrentPoint();
    //QVector<QPointF> getCompletedPath() const;
    QVariantList getCompletedPath() const;
    QVariantList getFullPath() const;
   // QVector<QPointF> getFullPath() const;
    float getForwardVectorRotation() const;

private:
    QVector<QPointF> path;
    QPointF curPoint, startPoint, endPoint, position;
    int currentPointIndex = 0;
    int taskStartTime;
    bool taskComplete = false;
    //QVector<QPointF> completedPath, fullPath;
    QVariantList completedPathList, fullPathList;
    QVector2D velocityDirection;

    VelocityCalculator velocityCalculator;

    void setPoints();
    void addCompletedPoint(const QPointF& point);

signals:
    void taskCompleteEvent();

};

#endif // GAMETASK_H
