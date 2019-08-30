
/************************************************************************/
// File Name: synch.c
// Description: Main function for SPD and SAD cases
//		Runs one simulation for a specific value of the parameters
//		alpha, epsilon and gamma.
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Non standard libraries
/************************************************************************/

#include "LatticeFunctions.h"
#include "UnimodalFunctions.h"
#include "Operators.h"
#include "VectorOperators.h"

/************************************************************************/
// General parameters for the simulation
/************************************************************************/

#include "Parameters.h"

/************************************************************************/
// SIMULATION
/************************************************************************/

int main(int argc, char *argv[])
{
	// Variable to control errors from functions
	int k;
	// Variable to go over each element of the network
	int node;
	// Variable to control the iterations
	int time_iteration;

	// Previous state of the system (t-1) and current state of the system (t)
	double original_previous[NODES], original_current[NODES];

	// Shadow orbits of the system for (t-1), (t) and normalized.
	double shadow_previous[NODES], shadow_current[NODES], normalized_shadow[NODES];

	// Global metrics over the lattice
	double average_original = 0;
	double deviation_original = 0;

	// Distances
	double initial_distance = 0;
	double current_distance = 0;

	// Global metrics for shadow orbits
	double average_shadow = 0;
	double deviation_shadow = 0;

	// Model parameters for the non delayed case
	double alpha, epsilon, gamma;

	// Normalization factor eta
	double eta;

	// Two files to be used to store data from simulation
	char file_name[40];
	char delta_file[40];

	// Name for the initial conditions file
	char conditions_name[40];

	// Declaration of 2 data files
	// One for the original orbit and one for the shadow orbit
	FILE *file_01, *file_02;

/************************************************************************/
// Data files initialization
/************************************************************************/

	if( argc != 4 )
	{
		printf("Use 3 input parameters: alpha, epsilon, gamma \n");
		exit(1);
	}

	// Get the model parameters
	sscanf(argv[1],"%lf",&alpha);
	sscanf(argv[2],"%lf",&epsilon);
	sscanf(argv[3],"%lf",&gamma);

	// Epsilon define the initial conditions. For each value there is a different set.
	sprintf(conditions_name, "ic_a_%.2lf_e_%.2lf.csv", alpha, epsilon);

	// Data for the original orbit
	sprintf(file_name, "sim_file_a_%.2lf_e_%.2lf_g_%.2lf.csv", alpha,epsilon,gamma);
	sprintf(delta_file, "sim_delta_a_%.2lf_e_%.2lf_g_%.2lf.csv", alpha,epsilon,gamma);

	// Open each file
	file_01 = fopen(file_name,"w+");
	if( file_01 == NULL)
		{
			printf("FILE 01 ERROR \n");
			exit(1);
		}

	file_02 = fopen(delta_file,"w+");
	if( file_02 == NULL)
		{
			printf("FILE 02 ERROR \n");
			exit(1);
		}

	eta = LF_NormalizationFactor(NODES,alpha);

/************************************************************************/
// Main iteration
/************************************************************************/

	for( time_iteration = 0 ; time_iteration < NUMBER_OF_ITERATIONS ; time_iteration++ )
	{

		// First iteration
		if( time_iteration == 0 )
		{
			// Read the iniital conditions from file
			k = VO_ReadFile(conditions_name,original_previous,NODES);
			// Add the initial delta to the initial state to create the shadow orbit
			k = VO_Delta(original_previous, shadow_previous, NODES, DELTA);
			// The current and previous states are equal for t = 0 and t = -1
			k = VO_Copy(original_previous,original_current,NODES);
			// Same case for the shadow orbit
			k = VO_Copy(shadow_previous,shadow_current,NODES);

			// Initial distance d0
			initial_distance = VO_Distance(original_current, shadow_current, NODES);
		}
		
		// For the other iterations we need to calculate the current state
		// using the previous states
		else
		{
			// We go over the whole network
			for( node = 0 ; node < NODES ; node++ )
			{
				// Equation (1) of the article for the SAD and SPD cases
				original_current[node] = (1 - epsilon)*UF_map(MU,original_previous[node]) +
				             (epsilon/eta)*OP_Sum_Open(node,original_previous,MU,alpha,NODES) +
										 (gamma/eta)*OP_Sub_Open(node,original_previous,MU,alpha,NODES);

				// Dynamical equation for the shadow orbit
				shadow_current[node] = (1 - epsilon)*UF_map(MU,shadow_previous[node]) +
									   (epsilon/eta)*OP_Sum_Open(node,shadow_previous,MU,alpha,NODES) +
									   (gamma/eta)*OP_Sub_Open(node,shadow_previous,MU,alpha,NODES);

				}
			}


/************************************************************************/
// Once the states are calculated, we calculate average, deviation and distance
// between the original orbit and the shadow orbit
/************************************************************************/

		average_original   = OP_Average(original_current,NODES);
		deviation_original = OP_Deviation(original_current,NODES,average_original);

		average_shadow = OP_Average(shadow_current,NODES);
		deviation_shadow = OP_Deviation(shadow_current,NODES,average_shadow);

		current_distance = VO_Distance(original_current, shadow_current, NODES);

/************************************************************************/
// After the transient, both orbits are saved in the specified file
/************************************************************************/

		if(time_iteration >= TRANSIENT)
		{
			fprintf(file_01,"%d \t",time_iteration);
			fprintf(file_02,"%d \t",time_iteration);
			for( node = 0 ; node < NODES ; node++ )
			{
				fprintf(file_01,"%1.16lf \t",original_current[node]);
				fprintf(file_02,"%1.16lf \t",shadow_current[node]);
			}
			fprintf(file_01,"%1.16lf \t %1.16lf \n",average_original,deviation_original);
			fprintf(file_02,"%1.16lf \t %1.16lf \n",average_shadow,deviation_shadow);
		}

/************************************************************************/
// Normalize the shadow orbit and update states
/************************************************************************/

		k = VO_Adjustment(shadow_current, original_current, normalized_shadow, NODES, initial_distance, current_distance);
		k = VO_Copy(normalized_shadow, shadow_current, NODES);
		k = VO_Copy(original_current,original_previous,NODES);
		k = VO_Copy(shadow_current,shadow_previous,NODES);

	}


/************************************************************************/
// Control of errors and close the files
/************************************************************************/

	printf("k value %d \n",k);
	fclose(file_01);
	fclose(file_02);

	return 0;
}
