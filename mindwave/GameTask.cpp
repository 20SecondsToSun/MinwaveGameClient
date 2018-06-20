#include "GameTask.h"
#include <QVector2D>
#include <QDebug>
#include <QtMath>
#include <QDateTime>

GameTask::GameTask()
{

}

GameTask::GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc)
{
    path = value;
    for(int i = 0; i<value.length(); i++)
    {
        fullPathList.append(value[i]);
    }

    velocityCalculator = velCalc;
}

void GameTask::setPath(const QVector<QPointF>& value)
{
    path = value;
}

void GameTask::init()
{
    taskComplete = false;
    currentPointIndex = 0;
    completedPathList.clear();
    setPoints();   
    addCompletedPoint(path[0]);
}

void GameTask::start()
{
   taskStartTime = QDateTime::currentMSecsSinceEpoch();
}

void GameTask::addCompletedPoint(const QPointF& point)
{
    // completedPath.push_back(point);
     completedPathList.append(point);
}

void GameTask::setPoints()
{
    startPoint = path[currentPointIndex];
    curPoint = startPoint;
    position = QPointF(0, 0);
    endPoint = path[currentPointIndex + 1];

    velocityDirection = QVector2D(endPoint - startPoint);
    velocityDirection.normalize();
}

void GameTask::update(int humanValue)
{
    if(taskComplete)
    {
        return;
    }

    QVector2D vec(endPoint - curPoint);

    auto velocity = velocityCalculator.calculate(humanValue);
    const float epsilon = 1.1f * velocity;

    if(vec.length() < epsilon)
    {
        curPoint = endPoint;
        addCompletedPoint(curPoint);

        currentPointIndex++;

        if(currentPointIndex < path.length() - 1)
        {
            setPoints();
        }
        else
        {
            taskComplete = true;
            emit taskCompleteEvent();
        }
    }
    else
    {
        position.setX(position.x() + velocity);
        position.setY(position.y() + velocity);

        curPoint.setX(startPoint.x() + position.x() * velocityDirection.x());
        curPoint.setY(startPoint.y() + position.y() * velocityDirection.y());

      //  qDebug()<< curPoint.x()<< curPoint.y();
    }
}

//QVector<QPointF> GameTask::getCompletedPath() const
//{
//    return completedPath;
//}

QVariantList GameTask::getCompletedPath() const
{
    return completedPathList;
}

QVariantList GameTask::getFullPath() const
{
    return fullPathList;
}

void GameTask::stop()
{
    // completedPath.clear();
     completedPathList.clear();
}

int GameTask::getCompletionTime() const
{
    return QDateTime::currentMSecsSinceEpoch() - taskStartTime;
}

QPointF GameTask::getStartPoint() const
{
    return startPoint;
}

QPointF GameTask::getCurPoint() const
{
    return curPoint;
}

float GameTask::getForwardVectorRotation() const
{
    QVector2D forwardVec(endPoint - startPoint);
    return qAtan2(forwardVec.y(), forwardVec.x());
}



