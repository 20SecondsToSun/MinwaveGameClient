#ifndef VELOCITYCALCULATOR_H
#define VELOCITYCALCULATOR_H

#include <QObject>

class VelocityCalculator
{
public:
    VelocityCalculator();
    VelocityCalculator(float minVelocity,
                       float maxVelocity,
                       float humanValueThresholdMin,
                       float humanValueThresholdMax = 100.0f,
                       float minBackVelocity = -5.0f,
                       float maxBackVelocity = 1.0f);

    float calculate(int humanValue);

    void  setLimits(float minVelocity,
                    float maxVelocity,
                    float humanValueThresholdMin,
                    float humanValueThresholdMax = 100.0f,
                    float minBackVelocity = -5.0f,
                    float maxBackVelocity = 1.0f);

private:
    float humanValueThresholdMax = 100;
    float humanValueThresholdMin = 60;

    float minVelocity = 0;
    float maxVelocity = 3;

    float minBackVelocity =  -5;
    float maxBackVelocity =  -1;

    bool backMove = false;

    template <typename T>
    T map(T value, T minIn, T maxIn, T minOut, T maxOut)
    {
        return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
    }
};

#endif // VELOCITYCALCULATOR_H
