#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QObject>
#include <QTimer>

class GameSession : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(float sessionTime READ sessionTime WRITE setSessionTime NOTIFY sessionTimeChanged)

    explicit GameSession(QObject *parent = nullptr);

    void start();
    void stop();

    void addTaskTime(float time);

    float allTaskCleanTime = 0;
    float sessionTime() const;
    void setSessionTime(float value);
    const int gameTimerMills = 10;

private:
    float _sessionTime = 0.0;
    int sessionStartTime, gameCleanTime;
    QTimer* sessionTimer;

signals:
    void sessionTimeChanged();
    void allTaskTimeChanged(float allTaskCleanTime);

public slots:
    void onSessionTimerUpdate();
};

#endif // GAMESESSION_H
