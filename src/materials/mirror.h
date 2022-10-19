#ifndef MIRROR_H
#define MIRROR_H
#include "material.h"
class Mirror :
    public Material
{
public:
 

    Mirror();

    Vector3D getReflectance(const Vector3D& n, const Vector3D& wo,
        const Vector3D& wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    double getIndexOfRefraction() const;
    Vector3D getDiffuseCoefficient() const;
};

#endif // !MIRROR_H


