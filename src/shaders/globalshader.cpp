#include "globalshader.h"
#include <math.h>

#define N_DIRECTIONS 10
#define N_BOUNCES 5

GlobalShader::GlobalShader(){
}

GlobalShader::GlobalShader(Vector3D at, Vector3D bgColor_){
	this->at = at;
    bgColor = bgColor_;
}

Vector3D GlobalShader::computeColor(const Ray& r, const vector<Shape*>& objList, const vector<PointLightSource>& lsList) const{
    Intersection its = Intersection();
    if (Utils::getClosestIntersection(r, objList, its)) {
        HemisphericalSampler hs = HemisphericalSampler();
        if(its.shape->getMaterial().hasDiffuseOrGlossy()){
            Vector3D Lind = Vector3D(0);
            if(r.depth == 0){
          
                for (size_t i = 0; i < N_DIRECTIONS; i++)
                {
                    Vector3D wj = hs.getSample(its.normal).normalized();
                    Ray r_bounced = Ray(its.itsPoint, wj, r.depth + 1);


                    if (Utils::hasIntersection(r_bounced, objList)) {
                        Vector3D wo = (r.o - its.itsPoint).normalized();
                        Vector3D li = computeColor(r_bounced, objList, lsList);
                        Vector3D rp = its.shape->getMaterial().getReflectance(its.normal, wo, wj);
                        Lind += Utils::multiplyPerCanal(li, rp);
                    }

                }
                Lind = Lind * (1 / (2 * M_PI * N_DIRECTIONS));
               
            }else{ //if (r.depth == N_BOUNCES) {
                Lind = this->at * its.shape->getMaterial().getDiffuseCoefficient();
            }/*else {
                Vector3D wo = r.o - its.itsPoint;
                wo = wo.normalized();
                Vector3D wr = its.normal * 2 * dot(wo, its.normal) - wo;
                Vector3D wn = its.normal;
                Ray rayWr = Ray(its.itsPoint, wr, r.depth + 1);
                Ray rayWn = Ray(its.itsPoint, wn, r.depth + 1);
                Vector3D lo_Wr = Vector3D(0);
                Vector3D lo_Wn = Vector3D(0);
                if(Utils::hasIntersection(rayWr,objList))
                    lo_Wr = computeColor(rayWr, objList, lsList);
                if(Utils::hasIntersection(rayWn,objList))
                    lo_Wn = computeColor(rayWn, objList, lsList);

                Lind = (lo_Wr + lo_Wn) * (1 / 4 * M_PI);
            }*/



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
            Vector3D wo = r.o - its.itsPoint;
            wo = wo.normalized();
            Vector3D wr = its.normal * 2 * dot(wo, its.normal) - wo;
            Ray reflectionRay = Ray(its.itsPoint, wr.normalized(), r.depth);
            return computeColor(reflectionRay, objList, lsList);

                
        }else if(its.shape->getMaterial().hasTransmission()){
            Vector3D wo = -r.d;
            //wo = wo.normalized();
            double etaT = its.shape->getMaterial().getIndexOfRefraction();
            Vector3D n = its.normal.normalized();
            double wo_n_prod = dot(wo, n);
            if(wo_n_prod < 0){
                n = -n;
                wo_n_prod = dot(wo,n);
                etaT = 1/etaT;
            }
            double insRot = 1 - (pow(etaT, 2) * (1 - pow(wo_n_prod, 2)));
            if (insRot >= 0){
                double t = -sqrt(insRot) + etaT * dot(wo, n);
                Vector3D wt = n * t - wo * etaT;
                Ray refractedRay = Ray(its.itsPoint, wt.normalized(), r.depth);
                return computeColor(refractedRay, objList, lsList);
                //return Vector3D(0);
            }
            else {
                Vector3D wr = n * 2 * wo_n_prod - wo;
                Ray reflectionRay = Ray(its.itsPoint, wr.normalized(), r.depth);
                return computeColor(reflectionRay, objList, lsList);
            }
        }
        
    }
    else
        return bgColor;
}
