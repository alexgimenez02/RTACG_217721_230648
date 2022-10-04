#include "phong.h"

Phong::Phong(double kd, double ks, double n){

	this->kd = kd;
	this->ks = ks;
	this->n = n;

}

Vector3D Phong::getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi)
{
	return Vector3D();
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
