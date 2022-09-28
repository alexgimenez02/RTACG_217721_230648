#include "depthintersectionshader.h"


Vector3D DepthIntersectionShader::colorFormula(double hitD, double maxD) const
{
    return Vector3D(0, 0, max((int)(1 - hitD/maxD), 0));
}

Vector3D DepthIntersectionShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const
{

    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its))
        return colorFormula(dot(its->itsPoint, Vector3D(1, 1, 1)), 666.0);
    else
        return bgColor;
}
