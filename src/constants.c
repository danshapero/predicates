
#include <float.h>

const double epsilon = DBL_EPSILON;
const double splitter = (1 << 27) + 1.0;

const double resulterrbound = (3.0 + 8.0 * epsilon) * epsilon;

const double ccwerrboundA = (3.0 + 16.0 * epsilon) * epsilon;
const double ccwerrboundB = (2.0 + 12.0 * epsilon) * epsilon;
const double ccwerrboundC = (9.0 + 64.0 * epsilon) * epsilon * epsilon;
const double o3derrboundA = (7.0 + 56.0 * epsilon) * epsilon;
const double o3derrboundB = (3.0 + 28.0 * epsilon) * epsilon;
const double o3derrboundC = (26.0 + 288.0 * epsilon) * epsilon * epsilon;
const double iccerrboundA = (10.0 + 96.0 * epsilon) * epsilon;
const double iccerrboundB = (4.0 + 48.0 * epsilon) * epsilon;
const double iccerrboundC = (44.0 + 576.0 * epsilon) * epsilon * epsilon;
const double isperrboundA = (16.0 + 224.0 * epsilon) * epsilon;
const double isperrboundB = (5.0 + 72.0 * epsilon) * epsilon;
const double isperrboundC = (71.0 + 1408.0 * epsilon) * epsilon * epsilon;
