
#include <stdlib.h>

#include <float.h>
#include <math.h>


typedef double (*orient2d_t)(const double *, const double *, const double *);

double * perturb_orient2d(const orient2d_t orientation,
                          const double ** points,
                          const size_t index,
                          const size_t grid_size)
{
  double x1[] = {points[0][0], points[0][1]};
  double x2[] = {points[1][0], points[1][1]};
  double x3[] = {points[2][0], points[2][1]};

  double x[] = {points[index][0], points[index][1]};
  for (size_t i = 0; i < grid_size; ++i) {
    x[0] = nextafter(x[0], x[0] - 1.0);
    x[1] = nextafter(x[1], x[1] - 1.0);
  }

  double * xs[] = {x1, x2, x3};
  xs[index][0] = x[0]; xs[index][1] = x[1];

  const size_t n = 2 * grid_size + 1;
  double * zs = calloc(sizeof(double), n * n);

  for (size_t i = 0; i < n; ++i) {
    xs[index][0] = x[0];
    for (size_t j = 0; j < n; ++j) {
      zs[n * i + j] = (*orientation)(xs[0], xs[1], xs[2]);
      const double xk = xs[index][0];
      xs[index][0] = nextafter(xk, xk + 1.0);
    }
    const double yk = xs[index][1];
    xs[index][1] = nextafter(yk, yk + 1.0);
  }

  return zs;
}


typedef double (*incircle_t)(const double *,
                             const double *,
                             const double *,
                             const double *);

double * perturb_incircle(const incircle_t incircle,
                          const double ** points,
                          const size_t index,
                          const size_t grid_size)
{
  double x1[] = {points[0][0], points[0][1]};
  double x2[] = {points[1][0], points[1][1]};
  double x3[] = {points[2][0], points[2][1]};
  double x4[] = {points[3][0], points[3][1]};

  double x[] = {points[index][0], points[index][1]};
  for (size_t i = 0; i < grid_size; ++i) {
    x[0] = nextafter(x[0], x[0] - 1.0);
    x[1] = nextafter(x[1], x[1] - 1.0);
  }

  double * xs[] = {x1, x2, x3, x4};
  xs[index][0] = x[0]; xs[index][1] = x[1];

  const size_t n = 2 * grid_size + 1;
  double * zs = calloc(sizeof(double), n * n);

  for (size_t i = 0; i < n; ++i) {
    xs[index][0] = x[0];
    for (size_t j = 0; j < n; ++j) {
      zs[n * i + j] = (*incircle)(xs[0], xs[1], xs[2], xs[3]);
      const double xk = xs[index][0];
      xs[index][0] = nextafter(xk, xk + 1.0);
    }
    const double yk = xs[index][1];
    xs[index][1] = nextafter(yk, yk + 1.0);
  }

  return zs;
}
