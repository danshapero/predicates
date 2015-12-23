
#include <stdlib.h>

#include <math.h>
#include <float.h>

#include "write_png.h"
#include <predicates.h>


int main(int argc, char ** argv)
{
  const double x1[] = {0.5, 0.5};
  const double x2[] = {12.0, 12.0};
  const double x3[] = {24.0, 24.0};

  const size_t nx = 256, ny = 256;
  double * z;

  z = perturb_orient2d(&orient2dfast, (const double *[]){x2, x3, x1}, 2, nx, ny);
  matrix_to_png("orientation1.png", nx, ny, z);
  free(z);

  z = perturb_orient2d(&orient2dfast, (const double *[]){x3, x1, x2}, 1, nx, ny);
  matrix_to_png("orientation2.png", nx, ny, z);
  free(z);

  z = perturb_orient2d(&orient2dfast, (const double *[]){x1, x2, x3}, 0, nx, ny);
  matrix_to_png("orientation3.png", nx, ny, z);
  free(z);

  return 0;
}
