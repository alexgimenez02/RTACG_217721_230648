#ifndef DEPTHINTERSECTIONSHADER_H
#define DEPTHINTERSECTIONSHADER_H
#include "shader.h"
#include "../core/utils.h"

class DepthIntersectionShader : public Shader {
public:
	DepthIntersectionShader();
    DepthIntersectionShader(Vector3D hitColor, Vector3D bgColor_);

    Vector3D colorFormula(double hitD, double maxD) const;
    virtual Vector3D computeColor(const Ray& r,
        const vector<Shape*>& objList,
        const vector<PointLightSource>& lsList) const;

    Vector3D hitColor;
};
#endif // !DEPTHINTERSECTIONSHADER_H


