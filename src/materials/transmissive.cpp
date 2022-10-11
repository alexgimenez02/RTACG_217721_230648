#include "transmissive.h"

Transmissive::Transmissive()
{
}

Vector3D Transmissive::getReflectance()
{
	return Vector3D();
}

bool Transmissive::hasSpecular()
{
	return false;
}

bool Transmissive::hasTransmission()
{
	return true;
}

bool Transmissive::hasDiffuseOrGlossy()
{
	return false;
}

double Transmissive::getIndexOfRefraction()
{
	return 0.0;
}
