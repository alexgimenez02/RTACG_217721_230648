#ifndef TRANSMISSIVE_H
#define TRANSMISSIVE_H

#include "material.h"
class Transmissive :
    public Material
{
public:
    double indRef;

    Transmissive(double indRef);

    bool hasSpecular();
    bool hasTransmission();
    bool hasDiffuseOrGlossy();
    double getIndexOfRefraction();

};

#endif // !TRANSMISSIVE_H



