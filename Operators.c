/************************************************************************/
/* File Name: Operators.c						*/
/* Description: Implementation of functions over functions for CML      */
/*  Calculates sums, averages and deviations for vectors                */
/* Author: Max Contreras - mecontrl@uc.cl				*/
/* Date: July 17 2016							*/
/************************************************************************/

#include "Operators.h"

/************************************************************************/
/* Function: OP_Sum							*/
/* Input: current node, past states vector, alpha, 			*/
/*	epsilon, Number of nodes 					*/
/* Return: double 							*/
/* Description: Calculates the sum of the lattice dynamics 		*/
/************************************************************************/

double OP_Sum(int current_node, double *x, double mu, double alpha, int total_number_of_nodes)
{
	double sum;
	double numerator;
	double denominator_01;
	double denominator_02;
	int m;

	sum = 0.0;

	for( m = 0 ; m < total_number_of_nodes ; m++)
	{
		// The sum must be taken over all the systems except the local term
		if( m == current_node )
		{
			sum = sum + 0.0;
		}
		else
		{
			numerator      = UF_logmap(mu,x[m]);
			denominator_01 = LF_CircularDistance(total_number_of_nodes,current_node,m);
			denominator_02 = pow(denominator_01,alpha);

			sum = sum + (numerator/denominator_02);

		}
	}

	return sum;
}


/************************************************************************/
/* Function: OP_Average																									*/
/* Input: states vector, Number of nodes 																*/
/* Return: double 									 																		*/
/* Description: Calculates the average of the vector										*/
/************************************************************************/

double OP_Average(double *x, int total_number_of_nodes)
{
	double average, all_nodes;
	int m;

	all_nodes = (double) total_number_of_nodes;
	average = 0.0;

	for( m = 0 ; m < total_number_of_nodes ; m++)
	{
		average = average + x[m]/all_nodes;

	}

	return average;
}

/************************************************************************/
/* Function: OP_Deviation																								*/
/* Input: states vector, number of nodes, average 											*/
/* Return: double 									 																		*/
/* Description: Calculates the deviation of the vector from the avg			*/
/************************************************************************/

double OP_Deviation(double *x, int total_number_of_nodes, double vector_average)
{
	double deviation;
	double sum, all_nodes;
	int m;

	sum = 0.0;
	all_nodes = (double) total_number_of_nodes;

	for( m = 0 ; m < total_number_of_nodes ; m++)
	{
		sum = sum + pow((x[m]-vector_average),2)/all_nodes;
	}

	deviation = sqrt(sum);

	return deviation;
}

/************************************************************************/
/* Function: OP_Sum_Open																								*/
/* Input: current node, past states vector, alpha, 											*/
/*							epsilon, Number of nodes 																*/
/* Return: double 																											*/
/* Description: Calculates the sum of the lattice dynamics 							*/
/*				Opens the sum in 2 terms for the advective model							*/
/************************************************************************/

double OP_Sum_Open(int current_node, double *x, double mu, double alpha, int total_number_of_nodes)
{
	double sum;
	double numerator;
	double denominator_01;
	double denominator_02;
	int j;
	int M;
	int p,s;
	//reference names. Change later!

	sum = 0.0;

	if( (total_number_of_nodes % 2) == 0)
	{
		M = total_number_of_nodes/2;
	}
	else
	{
		M = (total_number_of_nodes-1)/2;
	}

	for( j = 1 ; j <= M ; j++)
	{

		p = current_node - j;
		s = current_node + j;

		if( p < 0 )
		{
			p = total_number_of_nodes + (current_node - j);
		}

		if( s >= total_number_of_nodes)
		{
			s = (current_node + j) - total_number_of_nodes;
		}

		numerator      = UF_logmap(mu,x[p]) + UF_logmap(mu,x[s]);

		denominator_01 = LF_CircularDistance(total_number_of_nodes,current_node,s);
		denominator_02 = pow(denominator_01,alpha);

		sum = sum + (numerator/denominator_02);

	}

	return sum;
}



/************************************************************************/
/* Function: OP_Sub_Open																								*/
/* Input: current node, past states vector, alpha, 											*/
/*							epsilon, Number of nodes 																*/
/* Return: double 																											*/
/* Description: Calculates the substraction of the lattice dynamics 		*/
/*				Opens the operation in 2 terms for the advective model				*/
/************************************************************************/

double OP_Sub_Open(int current_node, double *x, double mu, double alpha, int total_number_of_nodes)
{
	double sum;
	double numerator;
	double denominator_01;
	double denominator_02;
	int j;
	int M;
	int p,s;
	//reference names. Change later!

	sum = 0.0;

	if( (total_number_of_nodes % 2) == 0)
	{
		M = total_number_of_nodes/2;
	}
	else
	{
		M = (total_number_of_nodes-1)/2;
	}

	for( j = 1 ; j <= M ; j++)
	{

		p = current_node - j;
		s = current_node + j;

		if( p < 0 )
		{
			p = total_number_of_nodes + (current_node - j);
		}

		if( s >= total_number_of_nodes)
		{
			s = (current_node + j) - total_number_of_nodes;
		}

		numerator      = UF_logmap(mu,x[s]) - UF_logmap(mu,x[p]) ;

		denominator_01 = LF_CircularDistance(total_number_of_nodes,current_node,s);
		denominator_02 = pow(denominator_01,alpha);

		sum = sum + (numerator/denominator_02);

	}

	return sum;
}
