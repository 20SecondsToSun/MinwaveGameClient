#include "MindWave.h"
#include <QDebug>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include "tools/MathTools.h"

MindWave::MindWave()
{

}

int MindWave::attention() const
{
    return _attention;
}

int MindWave::meditation() const
{
    return _meditation;
}

int MindWave::poorSignalLevel() const
{
    return _poorSignalLevel;
}

void MindWave::setAttention(int value)
{
    _attention = value;
    emit attentionChanged();
}

void MindWave::setMeditation(int value)
{
    _meditation = value;
    emit meditationChanged();
}

void MindWave::setPoorSignalLevel(int value)
{
    _poorSignalLevel = value;
//    if(value >= 0 && value < 50)
//    {
//        _poorSignalColor = "#009900";
//    }
//    else if(value >= 50 && value < 150)
//    {
//        _poorSignalColor = "#999900";
//    }
//    else if(value >= 150 && value <= 200)
//    {
//        _poorSignalColor = "#999999";
//    }

    if(value >= 66 && value <= 100)
    {
        _poorSignalColor = "#009900";
    }
    else if(value >= 30 && value <= 66)
    {
        _poorSignalColor = "#999900";
    }
    else if(value >= 0 && value <= 30)
    {
        _poorSignalColor = "#999999";
    }

    emit poorSignalLevelChanged();
}

QString MindWave::poorSignalColor() const
{
    return _poorSignalColor;
}

int MindWave::getAttentionDelta() const
{
    return _attention - _lastAttention;
}

int MindWave::getMeditationDelta() const
{
    return _meditation - _lastMeditation;
}

void MindWave::parse(const QString& data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    QJsonObject eSenseJson = jsonObj.value("eSense").toObject();
    int _poorSignalLevel = jsonObj.value("poorSignalLevel").toInt();

    const bool test = false;

    _lastAttention = _attention;
    _lastMeditation = _meditation;

    if(!test)
    {
        setAttention(eSenseJson.value("attention").toInt());
        setMeditation(eSenseJson.value("meditation").toInt());
    }
    else
    {
        int min = 50;
        int max = 100;
        int RandAtten = qrand() % ((max + 1) - min) + min;
        setAttention(RandAtten);
        int  RandMed = qrand() % ((100 + 1) - 0) + 0;
        setMeditation(RandMed);
    }
   //  qDebug()<<data;
    int signalValue = jsonObj.value("poorSignalLevel").toInt();
    int signalRemappedValue = MathTools::map<float>(signalValue, 0,  200, 100,  0);

    setPoorSignalLevel(signalRemappedValue);

    qDebug()<<"attention: "<<_attention <<"meditation: "<<_meditation <<"poorSignalLevel: "<<_poorSignalLevel;
}














