
/************************************************************************/
// File Name: VectorOperators.h
// Description: Interface for VectorOperators.c
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
//  Standard libraries
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/************************************************************************/
// Functions declarations
/************************************************************************/

int VO_Initialize(double *vector, int total_number_of_nodes);

int VO_Clean(double *vector, int total_number_of_nodes);

int VO_Copy(double *vector1, double *vector2, int total_number_of_nodes);

int VO_ReadFile(char *name_of_file, double *vector1, int total_number_of_nodes);

int VO_InitializeFile(char *name_of_file, int total_number_of_nodes);

int VO_InitializeFile_2(char *name_of_file, int total_number_of_nodes);

int VO_Delta(double *vector1, double *vector2, int total_number_of_nodes, double delta);

double VO_Distance(double *vector1, double *vector2, int total_number_of_nodes);

int VO_Adjustment(double *vector1, double *vector2, double *vector3, int total_number_of_nodes, double d_zero, double d_one);

int VO_LinearCombination(double *vector3, double parameter_1, double *vector1, double parameter_2, double *vector2, int total_number_of_nodes);
