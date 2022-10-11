#ifndef MIRROR_H
#define MIRROR_H
#include "material.h"
class Mirror :
    public Material
{
public:
 

    Mirror(Vector3D interrogante);

    Vector3D getReflectance();
    bool hasSpecular();
    bool hasTransmission() ;
    bool hasDiffuseOrGlossy() ;
    double getIndexOfRefraction();
};

#endif // !MIRROR_H


