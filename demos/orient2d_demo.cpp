
#include <cmath>
#include <cfloat>

#include <predicates.hpp>
#include "write_png.h"

using namespace predicates;

int main()
{
  const double x1[] = {0.5, 0.5};
  const double x2[] = {12.0, 12.0};
  const double x3[] = {24.0, 24.0};

  const size_t nx = 256, ny = 256;

  auto predicate1 = [&](const double * x) { return orient2dfast(x,  x2, x3); };
  auto predicate2 = [&](const double * x) { return orient2dfast(x3, x,  x2); };
  auto predicate3 = [&](const double * x) { return orient2dfast(x2, x3, x ); };

  double A[nx * ny];

  auto callback =
    [&](const double p, const double *, const size_t i, const size_t j)
    {
      A[nx * i + j] = p;
    };

  perturb2d(predicate1, x1, nx, ny, callback);
  matrix_to_png("orientation1.png", nx, ny, A);

  perturb2d(predicate2, x1, nx, ny, callback);
  matrix_to_png("orientation2.png", nx, ny, A);

  perturb2d(predicate3, x1, nx, ny, callback);
  matrix_to_png("orientation3.png", nx, ny, A);

  return 0;
}
