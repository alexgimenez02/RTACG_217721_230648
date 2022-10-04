#ifndef PHONG_H
#define PHONG_H
#include "material.h"
class Phong : public Material
{
    //Atributes
    double kd, ks; //Diffuse and specular respectivelly
    double ns; //Shininess

    //Methods
    Phong(double kd, double ks, double n);

    Vector3D getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi);
    bool hasSpecular();
    bool hasTransmission();
    bool hasDiffuseOrGlossy();
    double getIndexOfRefraction();

};
#endif //!PHONG_H