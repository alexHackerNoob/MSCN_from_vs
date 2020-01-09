#pragma once
/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class CRandom
{
public:
	CRandom(int i_seed);
	~CRandom();
	int iGetRandomInt(int i_min, int i_max);
	double iGetRandomDouble(double d_min, double d_max);
};

