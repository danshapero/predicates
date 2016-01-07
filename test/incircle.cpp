
#include <cassert>
#include <cfloat>
#include <cmath>

#include <predicates.hpp>

int main()
{

  /**
   * Test a really easy case
   */
  double x1[] = {1.0, 0.0};
  double x2[] = {0.0, 1.0};
  double x3[] = {-1.0, 0.0};

  double p[] = {0.0, nextafter(-1.0, 0.0)};
  double q[] = {0.0, nextafter(-1.0, -2.0)};

  assert(incircle(x1, x2, x3, p) > 0);
  assert(incircle(x1, x2, x3, q) < 0);

  return 0;
}
