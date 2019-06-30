
/************************************************************************/
// File Name: Operators.h
// Description: Interface for Operators.c
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Standard libraries
/************************************************************************/

#include <math.h>
#include <stdio.h>

/************************************************************************/
// Non standard libraries
/************************************************************************/

#include "LatticeFunctions.h"
#include "UnimodalFunctions.h"

/************************************************************************/
// Functions declarations
/************************************************************************/

double OP_Sum(int current_node, double *x, double mu, double alpha, int total_number_of_nodes);

double OP_Average(double *x, int total_number_of_nodes);

double OP_Deviation(double *x, int total_number_of_nodes, double vector_average);

double OP_Sum_Open(int current_node, double *x, double mu, double alpha, int total_number_of_nodes);

double OP_Sub_Open(int current_node, double *x, double mu, double alpha, int total_number_of_nodes);
