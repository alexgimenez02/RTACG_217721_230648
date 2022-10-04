#include "normalshader.h"

NormalShader::NormalShader(){}

NormalShader::NormalShader(Vector3D hitColor, Vector3D bgColor_)
{
	this->hitColor = hitColor;
}

Vector3D NormalShader::colorFormula(Vector3D normal) const
{
	return (normal + Vector3D(1.0 , 1.0 , 1.0)) / 2.0;
}

Vector3D NormalShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const
{
    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its))
        return colorFormula(its->normal);
    else
        return bgColor;
}

