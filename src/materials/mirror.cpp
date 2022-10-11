#include "mirror.h"

Mirror::Mirror(Vector3D wo){
	this->wo = wo;
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
	return false;
}

double Mirror::getIndexOfRefraction()
{
	return 0.0;
}
