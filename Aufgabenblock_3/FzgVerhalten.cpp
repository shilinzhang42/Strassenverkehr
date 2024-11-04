#include "FzgVerhalten.h"

FzgVerhalten::FzgVerhalten(Weg* pWeg) : p_pWeg(pWeg)
{
}


FzgVerhalten::~FzgVerhalten()
{
}


Weg* FzgVerhalten::getWeg() const
{
	return p_pWeg;
}