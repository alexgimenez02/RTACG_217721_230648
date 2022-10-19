#include "globalshader.h"

GlobalShader::GlobalShader(){
}

GlobalShader::GlobalShader(Vector3D at, Vector3D bgColor_){
	this->at = at;
    bgColor = bgColor_;
}

Vector3D GlobalShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const{
    Intersection its = Intersection();
    if (Utils::getClosestIntersection(r, objList, its)) {
        
        if(its.shape->getMaterial().hasDiffuseOrGlossy()){
            Vector3D Lind = Vector3D(0);
            Lind = this->at * its.shape->getMaterial().getDiffuseCoefficient();

            Vector3D Lo = Vector3D(0, 0, 0);
            for (int i = 0; i < lsList.size(); i++) {

                Vector3D Li = lsList.at(i).getIntensity(its.itsPoint);
                Vector3D wi = (lsList.at(i).getPosition() - its.itsPoint).normalized();
                double maxT = (lsList.at(i).getPosition() - its.itsPoint).length();

                Ray wiRay = Ray(its.itsPoint, wi, 0, Epsilon, maxT);
                Vector3D rp = its.shape->getMaterial().getReflectance(its.normal, (r.o - its.itsPoint).normalized(), wi);

                if (!Utils::hasIntersection(wiRay, objList)) {
                    Lo += Li * rp;
                }
            }
            return Lo + Lind;
        }else if(its.shape->getMaterial().hasSpecular()){
            // PSEUDO-CODE
            // Vector3D wr = computeReflectionDirection(ray.d,its.normal)
            /* Ray reflectionRay = Ray(its.point,wr,ray.depth+1)
                * color = ComputeColor(reflectionRay,objLit,lsList)
                * return color;
                */
            Vector3D wo = r.o - its.itsPoint;
            wo = wo.normalized();
            Vector3D wr = its.normal * 2 * dot(wo, its.normal) - wo;
            Ray reflectionRay = Ray(its.itsPoint, wr.normalized(), r.depth + 1);
            return computeColor(reflectionRay, objList, lsList);

                
        }else if(its.shape->getMaterial().hasTransmission()){
            /* PSEUDO-CODE
                * if !isTotalInternalReflection(...){
                *     wt = computeTransmissionDirection(...)
                *     refracRay = Ray(its.point,wt,ray.depth+1)
                *     color = ComputeColor(refracRay,objList,lsList)
                * } else{
                *     color = Specular reflection
                * }
                * return color;
                */
            Vector3D wo = r.o - its.itsPoint;
            wo = wo.normalized();
            double etaT = its.shape->getMaterial().getIndexOfRefraction();
            double wo_n_prod = dot(wo, its.normal);
            double insRot = 1 - (pow(etaT, 2) * (1 - pow(wo_n_prod, 2)));
            if (insRot >= 0){
                //double outRot = -sqrt(insRot) + etaT * wo_n_prod;
                //Vector3D wt = its.normal * outRot - wo * etaT;
                double t = -sqrt(insRot) + etaT * dot((its.itsPoint - r.o).normalized(), its.normal);
                Vector3D wt = its.normal * t - wo * etaT;
                Ray refractedRay = Ray(its.itsPoint, wt.normalized(), r.depth + 1);
                return computeColor(refractedRay, objList, lsList);
                //return Vector3D(0);
            }
            else {
                Vector3D wr = its.normal * 2 * wo_n_prod - wo;
                Ray reflectionRay = Ray(its.itsPoint, wr.normalized(), r.depth + 1);
                return computeColor(reflectionRay, objList, lsList);
            }
        }
        
    }
    else
        return bgColor;
}
