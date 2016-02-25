
#include <cassert>
#include <cfloat>
#include <cmath>

#include <vector>

#include <predicates.hpp>

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

  /**
   * Test a really easy case
   */
  {
    double x1[] = {1.0, 0.0};
    double x2[] = {0.0, 1.0};
    double x3[] = {-1.0, 0.0};

    double p[] = {0.0, nextafter(-1.0, 0.0)};
    double q[] = {0.0, nextafter(-1.0, -2.0)};

    assert(incircle(x1, x2, x3, p) > 0);
    assert(incircle(x1, x2, x3, q) < 0);
  }


  /**
   * Test a more interesting case
   */
  {
    // This integer is nice because it's a perfect square and can be written as
    // the sum of two squares in 14 different ways.
    const int n = 325;

    // Compute all the natural numbers `j` in increasing order such that
    // `n^2 - j^2` is an integer
    std::vector<int> s = sums_of_squares(n);

    // Select an offset so that we can move the entire circle around; this
    // allows us to alter the relative magnitudes of the points in order to
    // cause as much or as little floating-point accuracy loss as we like.
    const int k = s[s.size()/2];
    double x[] = {(double)k, -std::sqrt(n*n - k*k)};

    // Pick some other integer points on the circle of radius `n`.
    double q1[] = {(double)s[0] - x[0], std::sqrt(n*n - s[0]*s[0]) - x[1]};
    double q2[] = {(double)s[1] - x[0], std::sqrt(n*n - s[1]*s[1]) - x[1]};
    double q3[] = {(double)s[2] - x[0], std::sqrt(n*n - s[2]*s[2]) - x[1]};

    // Make 1D predicates out of the incircle predicate that we actually wish
    // to test by fixing the other three points to check against.
    auto predicate = [&](const double * q) { return incircle(q1, q2, q3, q); };

    // This is the callback for our perturbation routine.
    auto correct =
      [&](const double p, const double * q, const size_t, const size_t)
      {
        const double y[] = {q[0] - x[0], q[1] - x[1]};
        const double r2 = y[0]*y[0] + y[1]*y[1];

        if (r2 < n*n) assert(p > 0);
        else if (r2 > n*n) assert(p < 0);
      };

    double q4[] = {0.0, 0.0};
    perturb2d(predicate, q4, 256, 256, correct);
  }

  return 0;
}
