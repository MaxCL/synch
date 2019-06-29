
/************************************************************************/
// File Name: LatticeFunctions.c
// Description: Implementation of functions for a 1D lattice:
//	distance, normalization and parity.
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

#include "LatticeFunctions.h"

/************************************************************************/
// Function: LF_CircularDistance
// Input: Number of nodes, initial node and final node
// Return: integer k = min[ abs(ini-fin + kN) ]
// Description: Minimize the distance between 2 points in a circle
/************************************************************************/

int LF_CircularDistance(int total_number_of_nodes,int initial_node,int final_node)
{
	int mid_node, nodes_distance;
	int k, rf, r;

	if( initial_node == final_node)
	{
		return 0;
	}

	if( (total_number_of_nodes % 2) == 0 )
		mid_node = total_number_of_nodes/2;			//N is even
	else
		mid_node = (total_number_of_nodes -1)/2;		//N is odd

	nodes_distance = initial_node - final_node;

	if( nodes_distance > mid_node)
	{
		k = -1;
		rf = fabs(nodes_distance + k * total_number_of_nodes);
		r = floor(rf);
	}

	if( nodes_distance < -mid_node )
	{
		k = 1;
		rf = fabs(nodes_distance + k * total_number_of_nodes);
		r = floor(rf);
	}

	if( !((nodes_distance > mid_node )||( nodes_distance < -mid_node )) )
	{
		k = 0;
		rf = fabs(nodes_distance + k * total_number_of_nodes);
		r = floor(rf);
	}

	return r;
}


/************************************************************************/
// Function: LF_NormalizationFactor
// Input: Number of nodes, range of interactions parameter
// Return: A double with the value of the normalization factor
// Description: Calculates the sum of the distance to the power alpha
/************************************************************************/


double LF_NormalizationFactor(int total_number_of_nodes,double alpha)
{
	double sum;
	int maximum_distance;

// FOR NUMBER OF NODES EVEN

	if( (total_number_of_nodes % 2) == 0 )
	{
		maximum_distance = total_number_of_nodes/2;
		sum = 2/pow(maximum_distance,alpha);
		maximum_distance = maximum_distance - 1;
		while( maximum_distance != 0)
		{
			sum = sum + 2/pow(maximum_distance,alpha);
			maximum_distance = maximum_distance - 1;
		}

	}

//	FOR NUMBER OF NODES ODD
	else
	{
		maximum_distance = total_number_of_nodes/2;
		sum = 2/pow(maximum_distance,alpha);
		maximum_distance = maximum_distance - 1;
		while( maximum_distance != 0)
		{
			sum = sum + 2/pow(maximum_distance,alpha);
			maximum_distance = maximum_distance - 1;
		}
	}

	return sum;
}

/************************************************************************/
// Function: LF_IsEven
// Input: Number of nodes
// Return: 1 if the number is even, 0 if not
// Description: Procedure that determines the parity of a number
/************************************************************************/

int LF_IsEven(int total_number_of_nodes)
{
	if( total_number_of_nodes % 2 == 0)
		return 1;
	else
		return 0;
}
