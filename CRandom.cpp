#include "CRandom.h"



CRandom::CRandom(int i_seed)
{
	srand(i_seed);
}


CRandom::~CRandom()
{
}

int CRandom::iGetRandomInt(int i_min, int i_max)
{
	return rand()%(i_max - i_min + 1) + i_min;
}

double CRandom::iGetRandomDouble(double d_min, double d_max)
{
	double d_random_0_1 = (double)rand() / RAND_MAX;
	return d_min + d_random_0_1 * (d_max - d_min);
}
