
#include <cmath>
#include <cfloat>

#include <vector>
#include <iostream>

#include <predicates.hpp>
#include "write_png.h"

using namespace predicates;


bool is_square(int k)
{
  int q = int(std::round(std::sqrt(1.0 * k)));
  return q*q == k;
}


/**
 * Return a vector of all the integers `k` such that `n^2 - k^2` is a square
 */
std::vector<int> sums_of_squares(int n)
{
  std::vector<int> s;

  for (int k = 1; k < n; ++k)
    if (is_square(n*n - k*k))
      s.push_back(k);

  return s;
}


int main()
{
  const int n = 325;

  std::vector<int> s = sums_of_squares(n);

  // Pick out an integer `k` such that `n^2 - k^2` is an integer, and such
  // that `k` and `sqrt(n^2 - k^2)` are roughly equal.
  const int k = s[s.size()/2];
  double x[] = {(double)k, -std::sqrt(n*n - k*k)};

  // Pick some other integer points on the circle of radius `n`.
  double q1[] = {(double)s[0] - x[0], std::sqrt(n*n - s[0]*s[0]) - x[1]};
  double q2[] = {(double)s[1] - x[0], std::sqrt(n*n - s[1]*s[1]) - x[1]};
  double q3[] = {(double)s[2] - x[0], std::sqrt(n*n - s[2]*s[2]) - x[1]};

  const size_t nx = 256, ny = 256;
  double q4[] = {0.0, 0.0};
  for (size_t i = 0; i < nx / 2; ++i) {
    q4[0] = nextafter(q4[0], q4[0] - 1);
    q4[1] = nextafter(q4[1], q4[1] - 1);
  }

  auto predicate = [&](const double * q)
    { return incircle(q1, q2, q3, q); };

  double A[nx * ny];

  auto callback =
    [&](const double p, const double *, const size_t i, const size_t j)
    {
      A[nx * i + j] = p;
    };

  perturb2d(predicate, q4, nx, ny, callback);
  matrix_to_png("incircle.png", nx, ny, A);

  return 0;
}
