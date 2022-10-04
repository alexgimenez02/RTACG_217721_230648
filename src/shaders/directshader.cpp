#include "directshader.h"

DirectShader::DirectShader(){}


DirectShader::DirectShader(Vector3D hitColor, Vector3D bgColor_) {
	this->hitColor = hitColor;
}

Vector3D DirectShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<PointLightSource>& lsList) const
{
    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its))
        return hitColor;
    else
        return bgColor;
}
