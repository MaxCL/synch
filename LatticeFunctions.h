
/************************************************************************/
// File Name: LatticeFunctions.h
// Description: Interface for LatticeFunctions.c
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Standard libraries
/************************************************************************/

#include <math.h>
#include <stdio.h>

/************************************************************************/
// Functions declarations
/************************************************************************/

int LF_CircularDistance(int Total_number_of_nodes,int Initial_node,int Final_node);

double LF_NormalizationFactor(int total_number_of_nodes,double alpha);

int LF_IsEven(int total_number_of_nodes);
