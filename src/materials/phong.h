#ifndef PHONG_H
#define PHONG_H
#include "material.h"

class Phong : public Material
{
public:
    //Atributes
    Vector3D kd, ks; //Diffuse and specular respectivelly
    double ns; //Shininess

    //Methods
    Phong(Vector3D kd, Vector3D ks, double n);

    Vector3D getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const override;
    bool hasSpecular() const override;
    bool hasTransmission() const override;
    bool hasDiffuseOrGlossy() const override;
    double getIndexOfRefraction() const override;

};
#endif //!PHONG_H