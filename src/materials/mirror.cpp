#include "mirror.h"

Mirror::Mirror(Vector3D interrogante){

}

Vector3D Mirror::getReflectance()
{
	return Vector3D();
}

bool Mirror::hasSpecular()
{
	return true;
}

bool Mirror::hasTransmission()
{
	return false;
}

bool Mirror::hasDiffuseOrGlossy()
{
	return true;
}

double Mirror::getIndexOfRefraction()
{
	return 0.0;
}
