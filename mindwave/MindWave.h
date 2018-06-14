#ifndef MINDWAVE_H
#define MINDWAVE_H

#include <QObject>
#include <QString>

class MindWave : public QObject
{
    Q_OBJECT

public:
    MindWave();

    Q_PROPERTY(int attention READ attention WRITE setAttention NOTIFY attentionChanged)
    Q_PROPERTY(int meditation READ meditation WRITE setMeditation NOTIFY meditationChanged)
    Q_PROPERTY(int poorSignalLevel READ poorSignalLevel WRITE setPoorSignalLevel NOTIFY poorSignalLevelChanged)

    Q_INVOKABLE QString poorSignalColor() const;
    Q_INVOKABLE int getMeditationDelta() const;
    Q_INVOKABLE int getAttentionDelta() const;

     int attention() const;
     int meditation() const;
     int poorSignalLevel() const;

     void setAttention(int value);
     void setMeditation(int value);
     void setPoorSignalLevel(int value);

     void parse(const QString& data);

private:
     int _attention = 0;
     int _meditation = 0;

     int _lastAttention = 0;
     int _lastMeditation = 0;

     int _poorSignalLevel = 200;

     QString _poorSignalColor = "black";

signals:
    void attentionChanged();
    void meditationChanged();
    void poorSignalLevelChanged();
};

#endif // MINDWAVE_H
