#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int number_of_cores;

  int alpha;
  double d_alpha;

  int epsilon;
  double d_epsilon;

  int gamma = 0;
  double d_gamma;

  int n = 0;

  FILE *file_01;

  file_01 = fopen("cases_list","w+");
  if( file_01 == NULL)
  {
    printf("FILE cases_list ERROR \n");
    exit(1);
  }

  if( argc != 2 )
	{
		printf("Use 1 input parameter: number of cores\n");
		exit(1);
	}

  sscanf(argv[1],"%d",&number_of_cores);

  for( alpha = 0 ; alpha <= 300 ; alpha=alpha+5)
  {
    for( epsilon = 0 ; epsilon <= 100 ; epsilon=epsilon+5)
    {
      d_alpha = (double)alpha/100;
      d_epsilon = (double)epsilon/100;
//      for( gamma = 0 ; (gamma <=100) && (gamma <= epsilon) ; gamma = gamma +5 )
//      {
      d_gamma = (double)gamma/100;
      fprintf(file_01,"./synch %1.2lf %1.2lf %1.2lf &\n", d_alpha, d_epsilon, d_gamma);
      n++;
      if( (n%number_of_cores == 0))
      {
        fprintf(file_01,"wait\n");
      }

    }
  }

  printf("%d\n",n);
  return 0;
}
