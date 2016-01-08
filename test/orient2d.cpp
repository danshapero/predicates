
#include <cassert>
#include <cfloat>
#include <cmath>

#include <predicates.hpp>

using namespace predicates;

int main()
{
  /**
   * Test a really easy case
   */
  double x1[] = {0.0, 0.0};
  double x2[] = {1.0, 1.0};
  double x3[] = {0.0, 1.0};

  assert(orient2d(x1, x2, x3) > 0);
  assert(orient2d(x1, x3, x2) < 0);


  /**
   * Test a harder case -- 3 nearly colinear points
   */
  double q1[] = {0.5, 0.5};
  double q2[] = {12.0, 12.0};
  double q3[] = {24.0, 24.0};

  // Make 1D predicates out of the orientation predicate that we actually wish
  // to test by fixing the other two points to check against.
  // The orientation predicate is, in exact arithmetic, invariant to cyclic
  // permutations of the inputs, so we should test that our floating-point
  // version also respects this property by testing permutations of the inputs.
  auto predicate1 = [&](const double * q) { return orient2d(q,  q2, q3); };
  auto predicate2 = [&](const double * q) { return orient2d(q3, q,  q2); };
  auto predicate3 = [&](const double * q) { return orient2d(q2, q3, q); };

  // This is the callback for our perturbation routine; at every point, check
  // if it is above or below the diagonal; points above should have positive
  // orientation, points below negative, and 0 for points on the diagonal.
  auto correct =
    [](const double p, const double * q, const size_t, const size_t)
    {
      if (q[1] > q[0]) assert(p > 0);
      else if (q[1] < q[0]) assert(p < 0);
      else assert(p == 0.0);
    };

  // Check all points within a 256 x 256 grid of (0.5, 0.5).
  perturb2d(predicate1, q1, 256, 256, correct);
  perturb2d(predicate2, q1, 256, 256, correct);
  perturb2d(predicate3, q1, 256, 256, correct);


  return 0;
}
