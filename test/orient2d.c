
#include <stdlib.h>
#include <stddef.h>

#include <assert.h>
#include <float.h>
#include <math.h>

#include <predicates.h>

typedef double (*orientation_t)(const double *, const double *, const double *);

static
double * perturb(const orientation_t orientation,
                 const double ** ps,
                 const size_t k,
                 const size_t nx,
                 const size_t ny)
{
  double x1[] = {ps[0][0], ps[0][1]};
  double x2[] = {ps[1][0], ps[1][1]};
  double x3[] = {ps[2][0], ps[2][1]};
  double * xs[] = {x1, x2, x3};

  double * zs = calloc(sizeof(double), nx * ny);

  for (size_t i = 0; i < ny; ++i) {
    xs[k][0] = ps[k][0];
    for (size_t j = 0; j < nx; ++j) {
      const double z = (*orientation)(xs[0], xs[1], xs[2]);
      zs[nx * i + j] = z;
      xs[k][0] = nextafter(xs[k][0], xs[k][0] + 1.0);
    }
    xs[k][1] = nextafter(xs[k][1], xs[k][1] + 1.0);
  }

  return zs;
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

  const size_t nx = 256;
  const size_t ny = 256;
  double * zs = perturb(&orient2d, (const double*[]){q1, q2, q3}, 0, nx, ny);

  for (size_t i = 0; i < ny; ++i)
    for (size_t j = 0; j < nx; ++j) {
      const double z = zs[nx * i + j];
      if (i > j)
        assert(z > 0);
      else if (i < j)
        assert(z < 0);
    }

  free(zs);

  return 0;
}
