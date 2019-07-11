/************************************************************************/
// File Name: Eigenvalues.c
// Description: Implementation of functions for equations 11 and 12
//     This are reduced expressions of the linearized diffusion
//     and advection.
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

#include <math.h>
#include "LatticeFunctions.h"

/************************************************************************/
// Function: PSI_ODD
// Input: Number of nodes, number of eigenvalue, alpha.
// Return: double with the value of the sum in equation 11.
// Description: Calculates the eigenvalue for the A matrix
//    the diffusion term in the N odd case.
/************************************************************************/

double PSI_ODD(int Nodes, double k_number, double alpha_value)
{
	double sum;
	int m;
	double normalization;

	sum = 0.00;
	for( m = 1 ; m <= (Nodes-1)/2 ; m++ )
	{
		sum = sum + cos(2*M_PI*k_number*m/Nodes)/powl(m,alpha_value);
	}

	normalization = LF_NormalizationFactor(Nodes, alpha_value);
	sum = (2*sum)/normalization;

	return sum;
}

/************************************************************************/
// Function: PSI_EVEN
// Input: Number of nodes, number of eigenvalue, alpha.
// Return: double with the value of the sum in equation 11.
// Description: Calculates the eigenvalue for the A matrix
//    the diffusion term in the N even case.
/************************************************************************/

double PSI_EVEN(int Nodes, double k_number, double alpha_value)
{
	double sum;
	int m;
	double normalization;


	sum = 0.00;
	for( m = 1 ; m <= (Nodes/2) ; m++ )
	{
		sum = sum + cos(2*M_PI*k_number*m/Nodes)/powl(m,alpha_value);
	}

	normalization = LF_NormalizationFactor(Nodes, alpha_value);
	sum = (2*sum)/normalization - ( (0.5*powl(-1.0,k_number))/(normalization*powl(Nodes/2,alpha_value)) );

	return sum;
}

/************************************************************************/
// Function: MU_ODD
// Input: Number of nodes, number of eigenvalue, alpha.
// Return: double with the value of the sum in equation 12.
// Description: Calculates the eigenvalue for the B matrix
//    the advection term in the N odd case.
/************************************************************************/

double MU_ODD(int Nodes, double k_number, double alpha_value)
{
	double sum;
	int m;
	double normalization;


	sum = 0.00;
	for( m = 1 ; m <= (Nodes-1)/2 ; m++ )
	{
		sum = sum + sin(2*M_PI*k_number*m/Nodes)/powl(m,alpha_value);
	}

	normalization = LF_NormalizationFactor(Nodes, alpha_value);
	sum = (2*sum)/normalization;

	return sum;
}

/************************************************************************/
// Function: MU_EVEN
// Input: Number of nodes, number of eigenvalue, alpha.
// Return: double with the value of the sum in equation 12.
// Description: Calculates the eigenvalue for the B matrix
//    the advection term in the N even case.
/************************************************************************/

double MU_EVEN(int Nodes, double k_number, double alpha_value)
{
	double sum;
	int m;
	double normalization;

	sum = 0.00;
	for( m = 1 ; m <= (Nodes/2) ; m++ )
	{
		sum = sum + sin(2*M_PI*k_number*m/Nodes)/powl(m,alpha_value);
	}

	normalization = LF_NormalizationFactor(Nodes, alpha_value);
	sum = (2*sum)/normalization;

	return sum;
}
