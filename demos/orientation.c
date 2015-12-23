
#include <stdlib.h>

#include <math.h>
#include <float.h>

#include "write_png.h"
#include <predicates.h>


typedef double (*orientation)(const double *, const double *, const double *);

double o3(const double * x1, const double * x2, const double * x3)
{
  return orient2dfast(x1, x2, x3);
}

double o1(const double * x1, const double * x2, const double * x3)
{
  return orient2dfast(x2, x3, x1);
}

double o2(const double * x1, const double * x2, const double * x3)
{
  return orient2dfast(x3, x1, x2);
}


double * perturb(const double * x1, const double * x2, const double * x3,
                 const size_t nx, const size_t ny, orientation o)
{
  double x[] = {x1[0], x1[1]};

  double * zs = calloc(sizeof(double), nx * ny);

  for (size_t i = 0; i < ny; ++i) {
    x[0] = x1[0];
    for (size_t j = 0; j < nx; ++j) {
      const double z = (*o)(x, x2, x3);
      zs[nx * i + j] = z;
      x[0] = nextafter(x[0], x[0] + 1.0);
    }
    x[1] = nextafter(x[1], x[1] + 1.0);
  }

  return zs;
}



int main(int argc, char ** argv)
{
  double x1[] = {0.5, 0.5};
  double x2[] = {12.0, 12.0};
  double x3[] = {24.0, 24.0};

  const size_t nx = 256, ny = 256;

  double * z1 = perturb(x1, x2, x3, nx, ny, o1);
  matrix_to_png("orientation1.png", nx, ny, z1);
  free(z1);

  double * z2 = perturb(x1, x2, x3, nx, ny, o2);
  matrix_to_png("orientation2.png", nx, ny, z2);
  free(z2);

  double * z3 = perturb(x1, x2, x3, nx, ny, o3);
  matrix_to_png("orientation3.png", nx, ny, z3);
  free(z3);

  return 0;
}
