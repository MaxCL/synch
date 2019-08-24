#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int alpha;
  double d_alpha;

  int epsilon;
  double d_epsilon;

  int gamma;
  double d_gamma;

  for( alpha = 0 ; alpha <= 300 ; alpha++)
  {
    for( epsilon = 0 ; epsilon <= 100 ; epsilon++)
    {
      d_alpha = (double)alpha/100;
      d_epsilon = (double)epsilon/100;
      d_gamma = 0.0;

      printf("./synch %1.2lf %1.2lf %1.2lf &\n", d_alpha, d_epsilon, d_gamma);
      if( (epsilon != 0) && (epsilon%7 == 0) )
      {
        printf("wait\n");
      }

    }
  }


  return 0;
}
