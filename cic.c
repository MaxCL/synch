
/************************************************************************/
// File Name: cic.c
// Description: Program that generates the initial conditions
// for each epsilon creates one file.
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

	int epsilon;
	double d_epsilon;

	int alpha;
	double d_alpha;

	char conditions_name[50];

//Required initialization for the random seed
	RandomInitialise(237,7152);

	for( alpha = 0 ; alpha <= MAX_ALPHA ; alpha++ )
	{
		d_alpha = (double)alpha/100;

		for( epsilon = 0 ; epsilon <= MAX_EPSILON ; epsilon++ )
		{
			d_epsilon = (double)epsilon/100;

			// This name is consistent with the simulation
			sprintf(conditions_name, "ic_a_%.2lf_e_%.2lf.csv", d_alpha, d_epsilon);
			//This create the files with random values
			k = VO_InitializeFile_2(conditions_name,NODES);
		}

	}

	return k;
}
