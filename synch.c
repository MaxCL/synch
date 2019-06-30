
/************************************************************************/
// File Name: synch.c
// Description: Main function for SPD and SAD cases
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

int main(int argc, char *argv[])
{
	int k;
	int node;
	int time_iteration;

	double original_previous[NODES];
	double original_current[NODES];

	double shadow_previous[NODES];
	double shadow_current[NODES];

	double normalized_shadow[NODES];

	double average_original;
	double deviation_original;

	double initial_distance;
	double current_distance;

	double average_shadow;
	double deviation_shadow;

	double alpha, epsilon, gamma;

	char file_name[40];
	char conditions_name[40];
	char delta_file[40];
	char adjusted_file[40];
	char distance_file[40];

	FILE *file_01;
//	FILE *file_01, *file_02, *file_03, *file_04;

/*************************************************************************************************************************************************************************/

	if( argc != 4 )
	{
		printf("Use 3 input parameters: alpha, epsilon, gamma \n");
		exit(1);
	}

	sscanf(argv[1],"%lf",&alpha);
	sscanf(argv[2],"%lf",&epsilon);
	sscanf(argv[3],"%lf",&gamma);

	sprintf(conditions_name, "ic_e_%.2lf.csv", epsilon);

	sprintf(file_name, "sim_file_a_%.2lf_e_%.2lf_g_%.2lf.csv", alpha,epsilon,gamma);
//	sprintf(delta_file, "sim_delta_a_%.3lf_e_%.3lf_g_%.3lf.csv", alpha,epsilon,gamma);
//	sprintf(adjusted_file, "sim_adjt_a_%.3lf_e_%.3lf_g_%.3lf.csv", alpha,epsilon,gamma);
//	sprintf(distance_file,"sim_dist_a_%.2lf_e_%.2lf_g_%.3lf.csv", alpha,epsilon,gamma);

/*************************************************************************************************************************************************************************/

	file_01 = fopen(file_name,"w+");
	if( file_01 == NULL)
		{
			printf("FILE 01 ERROR \n");
			exit(1);
		}
/*
	file_02 = fopen(delta_file,"w+");
	if( file_02 == NULL)
		{
			printf("FILE 02 ERROR \n");
			exit(1);
		}

	file_03 = fopen(adjusted_file,"w+");
	if( file_03 == NULL)
		{
			printf("FILE 03 ERROR \n");
			exit(1);
		}

	file_04 = fopen(distance_file,"w+");
	if( file_04 == NULL)
		{
			printf("FILE 04 ERROR \n");
			exit(1);
		}
*/

/*************************************************************************************************************************************************************************/

	for( time_iteration = 0 ; time_iteration < NUMBER_OF_ITERATIONS ; time_iteration++ )
	{

//		fprintf(file_01,"%d \t",time_iteration);	// In the first column, the number of the iteration
//		fprintf(file_02,"%d \t",time_iteration);
//		fprintf(file_03,"%d",time_iteration);
//		fprintf(file_04,"%d \t",time_iteration);

		if( time_iteration == 0 )
		{

			k = VO_ReadFile(conditions_name,original_previous,NODES); //Reading the random initial conditions from file
			//k = VO_ReadFile(conditions_name,shadow_previous,NODES);

			k = VO_Delta(original_previous, shadow_previous, NODES, DELTA);			//Adding the delta for the shadow orbit

			k = VO_Copy(original_previous,original_current,NODES);						//The current and previous orbits are equal for t=0
			k = VO_Copy(shadow_previous,shadow_current,NODES);

			initial_distance = VO_Distance(original_current, shadow_current, NODES);		//Initial distance d0

//			for( node = 0 ; node < NODES ; node++ )
//			{
//				fprintf(file_01,"%1.16lf \t",original_current[node]);			//Printing the initial conditions
//				fprintf(file_02,"%1.16lf \t",shadow_current[node]);			//In the original and the shadow
//			}

		}
		else
		{
			for( node = 0 ; node < NODES ; node++ )
			{
				original_current[node] = (1 - epsilon)*UF_logmap(MU,original_previous[node]) +
											 (epsilon/LF_NormalizationFactor(NODES,alpha))*OP_Sum_Open(node,original_previous,MU,alpha,NODES) +
										 (gamma/LF_NormalizationFactor(NODES,alpha))*OP_Sub_Open(node,original_previous,MU,alpha,NODES);

				if(time_iteration >= 9945)
				{
//					fprintf(file_01,"%1.16lf \t",original_current[node]);
					shadow_current[node] = (1 - epsilon)*UF_logmap(MU,shadow_previous[node]) +
									   (epsilon/LF_NormalizationFactor(NODES,alpha))*OP_Sum_Open(node,shadow_previous,MU,alpha,NODES) +
									   (gamma/LF_NormalizationFactor(NODES,alpha))*OP_Sub_Open(node,shadow_previous,MU,alpha,NODES);

//				fprintf(file_02,"%1.16lf \t",shadow_current[node]);
				}

			}

		}

/*************************************************************************************************************************************************************************/

		average_original   = OP_Average(original_current,NODES);
		deviation_original = OP_Deviation(original_current,NODES,average_original);

		average_shadow = OP_Average(shadow_current,NODES);
		deviation_shadow = OP_Deviation(shadow_current,NODES,average_shadow);

		current_distance = VO_Distance(original_current, shadow_current, NODES);


//		fprintf(file_04,"%1.16lf \n", current_distance);		//Print d in the distance file - I will have to use python to get the log(di/d0)

		if(time_iteration >= 9945)
		{
			fprintf(file_01,"%d \t",time_iteration);
			fprintf(file_01,"%1.16lf \t %1.16lf \n",average_original,deviation_original);
//			fprintf(file_02,"%1.16lf \t %1.16lf \n",average_shadow,deviation_shadow);
		}


		k = VO_Adjustment(shadow_current, original_current, normalized_shadow, NODES, initial_distance, current_distance);

/*		for( node = 0 ; node < NODES ; node++ )
			{

				fprintf(file_03,"\t %1.16lf", normalized_shadow[node]);			//In the original and the shadow

			}
		fprintf(file_03,"\n");
*/


		k = VO_Copy(normalized_shadow, shadow_current, NODES);
		k = VO_Copy(original_current,original_previous,NODES);
		k = VO_Copy(shadow_current,shadow_previous,NODES);

	}

	printf("k value %d \n",k);

	fclose(file_01);
//	fclose(file_02);
//	fclose(file_03);
//	fclose(file_04);

	return 0;
}
