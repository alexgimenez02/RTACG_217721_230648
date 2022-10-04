#include "directshader.h"

DirectShader::DirectShader(){}


DirectShader::DirectShader(Vector3D hitColor, Vector3D bgColor_) {
	this->hitColor = hitColor;
}



Vector3D DirectShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<PointLightSource>& lsList) const
{
    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its)) {
        Vector3D Lo = Vector3D(0, 0, 0);
        for (size_t i = 0; i < lsList.size(); i++)
        {
            Vector3D Li = lsList.at(i).getIntensity(its->itsPoint);
            Vector3D rp = its->shape->getMaterial().getReflectance(its->normal, r.d, its->itsPoint - lsList.at(i).getPosition());
            int Vi = 0;
            if (r.maxT < (its->itsPoint - lsList.at(i).getPosition()).length()) Vi = 1;
            Lo += Li * rp * Vi;
        }
        return Lo;
    }
    else
        return bgColor;
}
