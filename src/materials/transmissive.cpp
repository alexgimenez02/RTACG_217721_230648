#include "transmissive.h"

Transmissive::Transmissive(double indRef, Vector3D wo)
{
	this->indRef = indRef;
	this->wo = wo;
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
	return indRef;
}
