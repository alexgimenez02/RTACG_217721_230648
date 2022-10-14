#include "globalshader.h"

GlobalShader::GlobalShader(){
}

GlobalShader::GlobalShader(Vector3D bgColor_){
	bgColor = bgColor_;
}

Vector3D GlobalShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const{
    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its)) {

        Vector3D Lo = Vector3D(0, 0, 0);
        for (int i = 0; i < lsList.size(); i++) {

            Vector3D Li = lsList.at(i).getIntensity(its->itsPoint);
            Vector3D wi = (lsList.at(i).getPosition() - its->itsPoint).normalized();
            double maxT = (lsList.at(i).getPosition() - its->itsPoint).length();

            Ray wiRay = Ray(its->itsPoint, wi, 0, Epsilon, maxT);
            Vector3D rp = its->shape->getMaterial().getReflectance(its->normal, (r.o - its->itsPoint).normalized(), wi);

            if (!Utils::hasIntersection(wiRay, objList)) {
                Lo += Li * rp;
            }

        }
        return Lo;
    }
    else
        return bgColor;
}
