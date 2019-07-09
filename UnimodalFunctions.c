
/************************************************************************/
// File Name: UnimodalFunctions.c
// Description: Local functions for a 1D lattice:
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

#include "UnimodalFunctions.h"


/************************************************************************/
// Function: Logistic map
// Input: parameter and current state
// Return: double
//  Description: Calculates the next iteration for a logistic map
/************************************************************************/

double UF_logmap(double r, double x)
{
	double y = 0.0;

	y = r * x * (1 - x);

	return y;
}

/************************************************************************/
// Function: Sine map
// Input: parameter and current state
// Return: double
//  Description: Calculates the next iteration for a sine map
/************************************************************************/

double UF_sin(double r, double x)
{
	double y = 0.0;

	y = r * sin(M_PI * x);

	return y;
}

/************************************************************************/
// Function: quadratic map
// Input: parameter and current state
// Return: double
//  Description: Calculates the next iteration for a quadratic map
/************************************************************************/

double UF_qmap(double r, double x)
{
	double y = 0.0;

	y = 1 - r * pow(x,2.0);

	return y;
}
