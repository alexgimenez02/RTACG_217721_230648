#include "depthintersectionshader.h"


DepthIntersectionShader::DepthIntersectionShader(){}

DepthIntersectionShader::DepthIntersectionShader(Vector3D hitColor, Vector3D bgColor_)
{
    this->hitColor = hitColor;
}


Vector3D DepthIntersectionShader::colorFormula(double hitD, double maxD) const
{
    double c1 = 1.0 - (hitD / maxD);
    Vector3D RGBColor = Vector3D(0, 0, 0);
    if (c1 > 0) {
        RGBColor.z = c1;
    }
    return RGBColor;
}

Vector3D DepthIntersectionShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const
{

    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its))
        return colorFormula(r.maxT, 6.66);
    else
        return bgColor;
}
