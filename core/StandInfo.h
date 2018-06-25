#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>

class StandInfo : public QObject
{
    Q_OBJECT
public:
    explicit StandInfo(QObject *parent = nullptr);

private:
    int standId = 1;

signals:

public slots:

};

#endif // STANDINFO_H
