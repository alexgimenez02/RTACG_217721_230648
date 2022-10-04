#ifndef NORMALSHADER_H
#define NORMALSHADER_H

#include "shader.h"
#include "../core/utils.h"

class NormalShader : public Shader
{
public:

    NormalShader();
    NormalShader(Vector3D hitColor, Vector3D bgColor_);

    Vector3D colorFormula(Vector3D normal) const;
    virtual Vector3D computeColor(const Ray& r,
        const vector<Shape*>& objList,
        const vector<PointLightSource>& lsList) const;

    Vector3D hitColor;

};
#endif // !NORMALSHADER_H