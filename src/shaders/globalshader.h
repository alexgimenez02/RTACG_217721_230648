#ifndef GLOBALSHADER_H
#define GLOBALSHADER_H

#include "shader.h"
#include "../core/utils.h"
#include "../core/hemisphericalsampler.h"

class GlobalShader : public Shader
{

public: 

    GlobalShader();
    GlobalShader(Vector3D at, Vector3D bgColor_);

      Vector3D computeColor(const Ray& r,
        const std::vector<Shape*>& objList,
        const std::vector<PointLightSource>& lsList) const;

    Vector3D bgColor;
    Vector3D at;


};

#endif // !GLOBALSHADER_H