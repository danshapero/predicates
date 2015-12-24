
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <assert.h>
#include <float.h>
#include <math.h>

#include <predicates.h>


bool correct(const size_t nx, const size_t ny, const double * zs)
{
  for (size_t i = 0; i < ny; ++i)
    for (size_t j = 0; j < nx; ++j) {
      const double z = zs[nx * i + j];
      if (i > j) assert(z > 0);
      else if (i < j) assert(z < 0);
    }

  return true;
}


int main(int argc, char **argv)
{
  // Test an easy case
  double x1[] = {0.0, 0.0};
  double x2[] = {1.0, 1.0};
  double x3[] = {0.0, 1.0};

  assert(orient2d(x1, x2, x3) > 0);
  assert(orient2d(x1, x3, x2) < 0);


  // Systematically test a harder case
  double q1[] = {0.5, 0.5};
  double q2[] = {12.0, 12.0};
  double q3[] = {24.0, 24.0};
  double * zs;

  const size_t n = 256;
  zs = perturb_orient2d(&orient2d, (const double *[]){q1, q2, q3}, 0, n);
  correct(n, n, zs);
  free(zs);

  zs = perturb_orient2d(&orient2d, (const double *[]){q2, q3, q1}, 2, n);
  correct(n, n, zs);
  free(zs);

  zs = perturb_orient2d(&orient2d, (const double *[]){q3, q1, q2}, 1, n);
  correct(n, n, zs);
  free(zs);

  return 0;
}
