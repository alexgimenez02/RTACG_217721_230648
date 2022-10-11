#ifndef TRANSMISSIVE_H
#define TRANSMISSIVE_H

#include "material.h"
class Transmissive :
    public Material
{
public:

    Transmissive();

    Vector3D getReflectance();
    bool hasSpecular();
    bool hasTransmission();
    bool hasDiffuseOrGlossy();
    double getIndexOfRefraction();

};

#endif // !TRANSMISSIVE_H



