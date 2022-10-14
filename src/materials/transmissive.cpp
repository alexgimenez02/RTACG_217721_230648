#include "transmissive.h"

Transmissive::Transmissive(double indRef)
{
	this->indRef = indRef;
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
