#include "phong.h"

Phong::Phong(double kd, double ks, double ns){

	this->kd = kd;
	this->ks = ks;
	this->ns = ns;
}

Vector3D Phong::getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi)
{
	Vector3D r = kd * dot(wi, n);
	Vector3D calc_n = n;
	calc_n.x *= (2 * dot(n, wi));
	calc_n.y *= (2 * dot(n, wi));
	calc_n.z *= (2 * dot(n, wi));
	Vector3D wr =  calc_n - wi;
	
	return r + (ks * pow(dot(wo,wr),ns));
}

bool Phong::hasSpecular()
{
	return false;
}

bool Phong::hasTransmission()
{
	return false;
}

bool Phong::hasDiffuseOrGlossy()
{
	return false;
}

double Phong::getIndexOfRefraction()
{
	return -1.0;
}
