
#include <cmath>
#include <cfloat>

#include <iostream>

#include <predicates.hpp>
#include "write_png.h"

using namespace predicates;

int main()
{
  const double x1[] = {1, 1};
  const double x2[] = {0, 2};
  const double x3[] = {-1, 1};
  double x4[] = {0, 0};

  const double q[] = {0.0, 1.0};
  std::cout << incirclefast(x1, x2, x3, q) << std::endl;

  const double r[] = {0.0, -1.0};
  std::cout << incirclefast(x1, x2, x3, r) << std::endl;

  const size_t nx = 256, ny = 256;
  for (size_t i = 0; i < nx / 2; ++i) {
    x4[0] = nextafter(x4[0], x4[0] - 1);
    x4[1] = nextafter(x4[1], x4[1] - 1);
  }

  auto predicate = [&](const double * x)
    { return incirclefast(x1, x2, x3, x); };

  double A[nx * ny];

  auto callback =
    [&](const double p, const double *, const size_t i, const size_t j)
    {
      A[nx * i + j] = p;
    };

  perturb2d(predicate, x4, nx, ny, callback);
  matrix_to_png("incircle.png", nx, ny, A);

  return 0;
}
