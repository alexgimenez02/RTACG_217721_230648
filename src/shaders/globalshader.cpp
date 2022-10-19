#include "globalshader.h"

GlobalShader::GlobalShader(){
}

GlobalShader::GlobalShader(Vector3D at, Vector3D bgColor_){
	this->at = at;
    bgColor = bgColor_;
}

Vector3D GlobalShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const{
    Intersection* its = new Intersection();
    if (Utils::getClosestIntersection(r, objList, *its)) {
        if (r.depth == 0) {
            if(its->shape->getMaterial().hasDiffuseOrGlossy()){
                Vector3D Lind = Vector3D(0);
                Lind = this->at * its->shape->getMaterial().getDiffuseCoefficient();

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
                return Lo + Lind;
            }else if(its->shape->getMaterial().hasSpecular()){
                // PSEUDO-CODE
                // Vector3D wr = computeReflectionDirection(ray.d,its->normal)
                /* Ray reflectionRay = Ray(its->point,wr,ray.depth+1)
                 * color = ComputeColor(reflectionRay,objLit,lsList)
                 * return color;
                 */
                Vector3D wr = cross(r.d, its->normal);
                //Vector3D wr = Vector3D(0);
                Ray reflectionRay = Ray(its->itsPoint, wr, r.depth + 1);
                return computeColor(reflectionRay, objList, lsList);
                
            }else if(its->shape->getMaterial().hasTransmission()){
                /* PSEUDO-CODE
                 * if !isTotalInternalReflection(...){
                 *     wt = computeTransmissionDirection(...)
                 *     refracRay = Ray(its->point,wt,ray.depth+1)
                 *     color = ComputeColor(refracRay,objList,lsList)
                 * } else{
                 *     color = Specular reflection
                 * }
                 * return color;
                 */
                double insRot = (1 - pow(its->shape->getMaterial().getIndexOfRefraction(), 2) * (1 - pow(dot(its->itsPoint - r.o, its->normal), 2)));
                if (insRot >= 0) {
                    //Calcular wt
                    double t = sqrt(insRot) - its->shape->getMaterial().getIndexOfRefraction() * dot(its->itsPoint - r.o, its->normal);
                    Vector3D wt = its->normal * t + (its->itsPoint - r.o) * its->shape->getMaterial().getIndexOfRefraction();
                    //Vector3D wt = Vector3D(0);
                    Ray refractedRay = Ray(its->itsPoint, wt, r.depth + 1);
                    return computeColor(refractedRay, objList, lsList);
                }
                else {
                    Vector3D wr = cross(r.d, its->normal);
                    Ray reflectionRay = Ray(its->itsPoint, wr, r.depth + 1);
                    return computeColor(reflectionRay, objList, lsList);
                }
            }
        }
        else {

        }
    }
    else
        return bgColor;
}
