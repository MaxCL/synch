
/************************************************************************/
// File Name: VectorOperators.h
// Description: Functions over Vectors
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Standard libraries
/************************************************************************/

#include <string.h>
#include <math.h>

/************************************************************************/
// Non standard libraries
/************************************************************************/

#include "VectorOperators.h"
#include "randomlib.h"

/************************************************************************/
// Function: VO_Initialize
// Input: vector, Number of nodes, decimal precision
// Return: nothing
// Description: Initializes a vector of the input size with random
//		in each component with the input precision
/************************************************************************/

int VO_Initialize(double *vector, int total_number_of_nodes)
{
	long int MAX_VALUE = 100000000;
	long int auxiliar_random;
	int n;

	srand(time(NULL));

	for( n = 0 ;  n < total_number_of_nodes ; n++ )
	{
		auxiliar_random = rand()%MAX_VALUE;
		vector[n] = ( (double)auxiliar_random )/MAX_VALUE;
	}

	return 0;

}

/************************************************************************/
// Function: VO_Clean
// Input: vector, Number of nodes
// Return: nothing
// Description: Put a zero in each component of the N-dim vector
/************************************************************************/

int VO_Clean(double *vector, int total_number_of_nodes)
{
	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		vector[n] = 0.0;
	}

	return 0;
}

/************************************************************************/
// Function: VO_Copy
// Input: vector1, vector2, Number of nodes
// Return: integer; 1 error / 0 ok
// Description: Copy the content of vector 1 into 2
/************************************************************************/

int VO_Copy(double *vector1, double *vector2, int total_number_of_nodes)
{
	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		vector2[n] = vector1[n];
	}

	return 0;
}

/************************************************************************/
// Function: VO_ReadFile
// Input: filename, vector1, Number of nodes
// Return: integer; 1 error / 0 ok
// Description: Copy the vector in the file into vector1
/************************************************************************/

int VO_ReadFile(char *name_of_file, double *vector1, int total_number_of_nodes)
{
	int node;
	double auxiliar_double;
	FILE *fpx_01;

	fpx_01 = fopen(name_of_file,"r");
	if(fpx_01 == NULL)
	{
		printf("Error reading file \n");
		exit(1);
	}

	for( node = 0 ; node < total_number_of_nodes ; node++)
	{
		fscanf(fpx_01,"%lf",&auxiliar_double);
		vector1[node] = auxiliar_double;
	}

	fclose(fpx_01);

	return 0;
}

/************************************************************************/
// Function: VO_InitializeFile
// Input: file name, Number of nodes, decimal precision
// Return: integer
// Description: Initializes a file with random numbers
// 				with the input precision
/************************************************************************/

int VO_InitializeFile(char *name_of_file, int total_number_of_nodes)
{
	long int MAX_VALUE = 100000000;
	long int auxiliar_random;
	double auxiliar_double;
	int n;
	FILE *fpx_02;

	fpx_02 = fopen(name_of_file,"w+");
	if(fpx_02 == NULL)
	{
		printf("Error reading file \n");
		exit(1);
	}

	for( n = 0 ;  n < total_number_of_nodes ; n++ )
	{
		auxiliar_random = rand()%MAX_VALUE;
		auxiliar_double = ( (double)auxiliar_random )/MAX_VALUE;
		fprintf(fpx_02,"%.16lf",auxiliar_double);

		if( n == (total_number_of_nodes-1) )
		{
			continue;
		}
		else
		{
			fprintf(fpx_02, "\t");

		}
	}

	fclose(fpx_02);
	return 0;

}

/************************************************************************/
// Function: VO_InitializeFile_2
// Input: file name, Number of nodes, decimal precision
// Return: integer
// Description: Initializes two sets of files one with random
//		numbers and the other with a 1E-8 to calculate the Lyapunov exponent
/************************************************************************/

int VO_InitializeFile_2(char *name_of_file, int total_number_of_nodes)
{
	double auxiliar_double;
	double rmin = 0.000;
	double rmax = 1.000;
	int n;
	FILE *fpx_02;

	fpx_02 = fopen(name_of_file,"w+");
	if(fpx_02 == NULL)
	{
		printf("Error opening file \n");
		exit(1);
	}

	for( n = 0 ;  n < total_number_of_nodes ; n++ )
	{

		auxiliar_double = RandomDouble(rmin,rmax);
		fprintf(fpx_02,"%.16lf",auxiliar_double);

		if( n != (total_number_of_nodes-1) )
		{
			fprintf(fpx_02, "\t");
		}
		else
		{
			continue;
		}
	}

	fclose(fpx_02);

	return 0;

}

/************************************************************************/
// Function: VO_Delta
// Input: vector1, vector2, Number of nodes
// Return: integer; 1 error / 0 ok
// Description: Copy the content of vector 1 into 2 + delta
/************************************************************************/

int VO_Delta(double *vector1, double *vector2, int total_number_of_nodes, double delta)
{
	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		vector2[n] = vector1[n] + delta;
	}

	return 0;
}

/************************************************************************/
// Function: VO_Distance
// Input: vector1, vector2, Number of nodes
// Return: double
// Description: return the euclidean distance between the vectors
/************************************************************************/

double VO_Distance(double *vector1, double *vector2, int total_number_of_nodes)
{
	double distance = 0.0;
	double sum = 0.0;

	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		sum = sum + pow(vector2[n] - vector1[n] , 2);
	}

	distance = sqrt(sum);

	return distance;
}

/************************************************************************/
// Function: VO_Adjustment
// Input: vector1, vector2, vector3, Number of nodes, distance 1 and 2
// Return: integer; 1 error / 0 ok
// Description: Readjust v1 so its separation is d0 and is in the same
//			direction as d1 with respect to v2 (put it in v3)
//			Then v2 is the original orbit.
/************************************************************************/

int VO_Adjustment(double *vector1, double *vector2, double *vector3, int total_number_of_nodes, double d_zero, double d_one)
{
	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		vector3[n] = vector2[n] + (d_zero/d_one)*(vector1[n] - vector2[n]);
	}

	return 0;
}

/************************************************************************/
// Function: VO_LinearCombination
// Input: vector1, vector2, vector3, 2 parameters and the number of nodes
// Return: integer; 1 error / 0 ok
// Description: Put in v3 the linear combination of v1 and v2
//				v3 = p1 x v1 + p2 x v2
/************************************************************************/

int VO_LinearCombination(double *vector3, double parameter_1, double *vector1, double parameter_2, double *vector2, int total_number_of_nodes)
{
	int n;

	for( n = 0 ; n < total_number_of_nodes ; n++ )
	{
		vector3[n] = parameter_1*vector1[n] + parameter_2*vector2[n];
	}

	return 0;

}
