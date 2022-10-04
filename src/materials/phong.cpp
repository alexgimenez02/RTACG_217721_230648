#include "phong.h"

Phong::Phong(Vector3D kd, Vector3D ks, double n)
{
	this->kd = kd;
	this->ks = ks;
	this->ns = ns;
}

Vector3D Phong::getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const
{
	Vector3D r = kd * dot(wi, n);
	Vector3D calc_n = n;
	calc_n.x *= (2 * dot(n, wi));
	calc_n.y *= (2 * dot(n, wi));
	calc_n.z *= (2 * dot(n, wi));
	Vector3D wr =  calc_n - wi;
	
	return r + (ks * pow(dot(wo,wr),ns));
}

bool Phong::hasSpecular() const
{
	return false;
}

bool Phong::hasTransmission() const
{
	return false;
}

bool Phong::hasDiffuseOrGlossy() const
{
	return false;
}

double Phong::getIndexOfRefraction() const
{
	return -1.0;
}
