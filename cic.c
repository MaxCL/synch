
/************************************************************************/
// File Name: cic.c
// Description: Program that generates the initial conditions
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Non standard libraries
/************************************************************************/

#include "VectorOperators.h"
#include "randomlib.h"

#include "Parameters.h"

/************************************************************************/
// Main Function
/************************************************************************/

int main(void)
{
	int k;
	int n;
	double epsilon;
	char conditions_name[50];

//Required initialization for the random seed
	RandomInitialise(1237,8151);

	for( n = 0 ; n <= FACTOR ; n++ )
	{
		epsilon = (double)n/FACTOR;

		// This name is consistent with the simulation
		sprintf(conditions_name, "ic_e_%.2lf.csv", epsilon);

//This create the files with random values
		k = VO_InitializeFile_2(conditions_name,NODES);

	}

	return k;
}
