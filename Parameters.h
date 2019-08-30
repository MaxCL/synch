
/************************************************************************/
// File Name: Parameters.h
// Description: General parameters for the simulations
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

// Number of elements in the network
#define NODES 201

// Number of iterations: Transient 10,000
#define NUMBER_OF_ITERATIONS 7101

// Time when transient ends
#define TRANSIENT 7000

// Parameter for the logistic map - chaotic state
#define MU 4.00

// Initial diference between the original orbit and the
// shadow orbit used to calculate the Lyapunov exponent
#define DELTA 0.00000001

// Factor for random numbers precision
#define FACTOR 100.0

// Range of alpha parameter *100
#define MAX_ALPHA 300

// Range of epsilon parameter *100
#define MAX_EPSILON 100
