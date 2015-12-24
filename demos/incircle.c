
#include <stdlib.h>

#include <math.h>
#include <float.h>

#include "write_png.h"
#include <predicates.h>


int main(int argc, char ** argv)
{
  // Three points on the circle of radius 12 about the point 12.5.
  double x1[] = {12.0, 12.5};
  double x2[] = {0.0, 24.5};
  double x3[] = {-12.0, 12.5};
  double x4[] = {0.0, 0.5};

  const double n = 128;

  double * z;
  z = perturb_incircle(&incirclefast, (const double *[]){x1, x2, x3, x4}, 3, n);

  matrix_to_png("incircle.png", 2*n+1, 2*n+1, z);
  free(z);

  return 0;
}
