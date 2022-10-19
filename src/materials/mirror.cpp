#include "mirror.h"

Mirror::Mirror(){}

Vector3D Mirror::getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const
{
	return Vector3D();
}

bool Mirror::hasSpecular() const
{
	return true;
}

bool Mirror::hasTransmission() const
{
	return false;
}

bool Mirror::hasDiffuseOrGlossy() const
{
	return false;
}

double Mirror::getIndexOfRefraction() const
{
	return 0.0;
}

Vector3D Mirror::getDiffuseCoefficient() const
{
	return Vector3D();
}
