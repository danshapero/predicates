
#include <float.h>

#define EPS (DBL_EPSILON / 2)

const double epsilon = EPS;
const double splitter = ((DBL_MANT_DIG + 1) >> 1) + 1.0;

const double resulterrbound = (3.0 + 8.0 * EPS) * EPS;

const double ccwerrboundA = (3.0 + 16.0 * EPS) * EPS;
const double ccwerrboundB = (2.0 + 12.0 * EPS) * EPS;
const double ccwerrboundC = (9.0 + 64.0 * EPS) * EPS * EPS;
const double o3derrboundA = (7.0 + 56.0 * EPS) * EPS;
const double o3derrboundB = (3.0 + 28.0 * EPS) * EPS;
const double o3derrboundC = (26.0 + 288.0 * EPS) * EPS * EPS;
const double iccerrboundA = (10.0 + 96.0 * EPS) * EPS;
const double iccerrboundB = (4.0 + 48.0 * EPS) * EPS;
const double iccerrboundC = (44.0 + 576.0 * EPS) * EPS * EPS;
const double isperrboundA = (16.0 + 224.0 * EPS) * EPS;
const double isperrboundB = (5.0 + 72.0 * EPS) * EPS;
const double isperrboundC = (71.0 + 1408.0 * EPS) * EPS * EPS;
