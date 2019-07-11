/************************************************************************/
// File Name: Eigenvalues.h
// Description: Interface for Eigenvalues.c
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Standard libraries
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>

/************************************************************************/
// Functions declarations
/************************************************************************/

double PSI_ODD(int Nodes, double k_number, double alpha_value);
double PSI_EVEN(int Nodes, double k_number, double alpha_value);
double MU_ODD(int Nodes, double k_number, double alpha_value);
double MU_EVEN(int Nodes, double k_number, double alpha_value);
