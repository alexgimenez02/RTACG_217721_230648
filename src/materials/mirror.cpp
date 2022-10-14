#include "mirror.h"

Mirror::Mirror(){}

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
