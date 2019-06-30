
/************************************************************************/
// File Name: randomlib.h
// Description: Interface for randomlib.c
// Author: Max Contreras - mecontrl@uc.cl
// Date: July 2016 @ Complex Systems PUC Rio - Brazil
/************************************************************************/

/************************************************************************/
// Functions declarations
/************************************************************************/

void   RandomInitialise(int,int);

double RandomUniform(void);

double RandomGaussian(double,double);

int    RandomInt(int,int);

double RandomDouble(double,double);
