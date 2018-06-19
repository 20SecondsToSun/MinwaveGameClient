#include "GameTask.h"
#include <QVector2D>
#include <QDebug>

GameTask::GameTask()
{

}

GameTask::GameTask(const QVector<QPointF>& value)
{
    path = value;
}

void GameTask::setPath(const QVector<QPointF>& value)
{
    path = value;
}

void GameTask::start()
{
    taskComplete = false;
    currentPointIndex = 0;
    setPoints();
    completedPath.push_back(path[0]);
}

void GameTask::setPoints()
{
    startPoint = path[currentPointIndex];
    curPoint = startPoint;
    position = QPointF(0, 0);
    endPoint = path[currentPointIndex + 1];

    velocityDirection = QVector2D(endPoint - startPoint);
    velocityDirection.normalize();

   // qDebug()<<velocityDirection.x()<< velocityDirection.y();
   // qDebug()<<"--------------";

}

void GameTask::update()
{
    if(taskComplete)
    {
        return;
    }

    QVector2D vec(endPoint - curPoint);
    const float epsilon = 0.1;

    if(vec.length() < epsilon)
    {
        curPoint = endPoint;
        completedPath.push_back(curPoint);

        currentPointIndex++;

        if(currentPointIndex < path.length() - 1)
        {
            setPoints();
        }
        else
        {
            taskComplete = true;
        }
    }
    else
    {
        position.setX(position.x() + 1);
        position.setY(position.y() + 1);

        curPoint.setX(startPoint.x() + position.x() * velocityDirection.x());
        curPoint.setY(startPoint.y() + position.y() * velocityDirection.y());
        qDebug()<<curPoint.x()<<curPoint.y();
    }
}

QVector<QPointF> GameTask::getCompletedPath() const
{
    return completedPath;
}

void GameTask::stop()
{

}

QPointF GameTask::getStartPoint() const
{
    return startPoint;
}

QPointF GameTask::getCurPoint() const
{
    return curPoint;
}


