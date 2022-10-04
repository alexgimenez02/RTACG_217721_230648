#ifndef DIRECTSHADER_H
#define DIRECTSHADER_H

#include "shader.h"
#include "../core/utils.h"
class DirectShader : public Shader
{
public:
    Vector3D hitColor;

    DirectShader();
    DirectShader(Vector3D hitColor, Vector3D bgColor_);

    Vector3D computeColor(const Ray& r,
        const vector<Shape*>& objList,
        const vector<PointLightSource>& lsList) const;

    Vector3D bgColor;
};

#endif // !DIRECTSHADER_H