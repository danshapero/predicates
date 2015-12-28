
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <predicates.h>

typedef struct
{
  const double x;
  const double y;
} point_t;


double orientation(const point_t * p1, const point_t * p2, const point_t * p3)
{
  return orient2d(&p1->x, &p2->x, &p3->x);
}


typedef struct
{
  size_t num_points;
  point_t ** points;
} polygon_t;


void destroy_polygon(polygon_t * p)
{
  free(p->points);
  p->num_points = 0;
}


polygon_t make_polygon(const size_t num_points, ...)
{
  polygon_t p = {.num_points = num_points,
                 .points = calloc(num_points, sizeof(point_t *))};

  va_list args;
  va_start(args, num_points);

  for (size_t k = 0; k < num_points; ++k)
    p.points[k] = va_arg(args, point_t *);

  va_end(args);

  return p;
}


bool is_convex(const polygon_t * p)
{
  const size_t n = p->num_points;
  point_t ** const ps = p->points;
  if (n < 3) return true;

  const double initial_orientation = orientation(ps[0], ps[1], ps[2]);
  for (size_t k = 1; k < n; ++k) {
    if (orientation(ps[k], ps[(k + 1) % n], ps[(k + 2) % n])
        * initial_orientation < 0)
      return false;
  }

  return true;
}


int main(int argc, char ** argv)
{
  point_t p1 = {.x = 0.5, .y = 0.5};
  point_t p2 = {.x = 12.0, .y = 12.0};
  point_t p3 = {.x = 24.0, .y = 24.0};

  const size_t n = 128;
  double * z = perturb_orient2d(
    &orient2dfast, (const double *[]){&p2.x, &p3.x, &p1.x}, 2, n
  );

  free(z);
  return 0;
}
