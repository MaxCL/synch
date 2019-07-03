/************************************************************************/
/* Program: 	Create Initial Conditions 								*/
/* Input: No input required												*/
/* Output: Create a set of files with random initial conditions			*/
/*			for each value of epsilon, with fixed alpha					*/
/* Description: Uses the randomlib library to create random values 		*/
/*				in [0,1] for each node. 								*/
/************************************************************************/

#include "VectorOperators.h"
#include "randomlib.h"

#include "Parameters.h"

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

		sprintf(conditions_name, "ic_e_%.2lf.csv", epsilon);

//This create the files with random values
		k = VO_InitializeFile_2(conditions_name,NODES);

	}

	return k;
}
