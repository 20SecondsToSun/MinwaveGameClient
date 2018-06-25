#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>

class StandData : public QObject
{
    Q_OBJECT
public:
    explicit StandData(QObject *parent = nullptr);

private:
    int standId = 1;

signals:

public slots:

};

#endif // STANDINFO_H
