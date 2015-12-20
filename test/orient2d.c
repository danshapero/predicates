
#include <assert.h>
#include <float.h>

#include <predicates.h>

int main(int argc, char **argv)
{
  double x1[] = {0.0, 0.0};
  double x2[] = {1.0, 1.0};
  double x3[] = {0.0, 1.0};

  assert(orient2d(x1, x2, x3) > 0);
  assert(orient2d(x1, x3, x2) < 0);

  double x4[] = {2.0, 2.0 * (1 + DBL_EPSILON)};
  assert(orient2d(x1, x2, x4) > 0);

  return 0;
}
