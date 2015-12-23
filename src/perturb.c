
#include <stdlib.h>

#include <float.h>
#include <math.h>

typedef double (*orient2d_t)(const double *, const double *, const double *);

double * perturb_orient2d(const orient2d_t orientation,
                          const double ** points,
                          const size_t index,
                          const size_t nx,
                          const size_t ny)
{
  double x1[] = {points[0][0], points[0][1]};
  double x2[] = {points[1][0], points[1][1]};
  double x3[] = {points[2][0], points[2][1]};
  double * xs[] = {x1, x2, x3};

  double * zs = calloc(sizeof(double), nx * ny);

  for (size_t i = 0; i < ny; ++i) {
    xs[index][0] = points[index][0];
    for (size_t j = 0; j < nx; ++j) {
      zs[nx * i + j] = (*orientation)(xs[0], xs[1], xs[2]);
      const double xk = xs[index][0];
      xs[index][0] = nextafter(xk, xk + 1.0);
    }
    const double yk = xs[index][1];
    xs[index][1] = nextafter(yk, yk + 1.0);
  }

  return zs;
}
