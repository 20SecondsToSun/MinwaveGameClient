#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QObject>

class GameSession : public QObject
{
    Q_OBJECT
public:
    explicit GameSession(QObject *parent = nullptr);

    void init();
    void addTaskTime(float time);

    float allTaskCleanTime = 0;

signals:

public slots:
};

#endif // GAMESESSION_H
