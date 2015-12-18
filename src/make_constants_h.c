
#include <stdio.h>

/**
 * Initialize variables used for exact arithmetic.
 */

typedef struct error_bounds
{
  double epsilon;
  double splitter;

  double resulterrbound;

  double ccwerrboundA;
  double ccwerrboundB;
  double ccwerrboundC;

  double o3derrboundA;
  double o3derrboundB;
  double o3derrboundC;

  double iccerrboundA;
  double iccerrboundB;
  double iccerrboundC;

  double isperrboundA;
  double isperrboundB;
  double isperrboundC;
} error_bounds_t;


/*****************************************************************************/
/*                                                                           */
/*  compute_error_bounds()   Initialize the variables for exact arithmetic.  */
/*                                                                           */
/*  `epsilon' is the largest power of two such that 1.0 + epsilon = 1.0 in   */
/*  floating-point arithmetic.  `epsilon' bounds the relative roundoff       */
/*  error.  It is used for floating-point error analysis.                    */
/*                                                                           */
/*  `splitter' is used to split floating-point numbers into two half-        */
/*  length significands for exact multiplication.                            */
/*                                                                           */
/*  I imagine that a highly optimizing compiler might be too smart for its   */
/*  own good, and somehow cause this routine to fail, if it pretends that    */
/*  floating-point arithmetic is too much like real arithmetic.              */
/*                                                                           */
/*  Don't change this routine unless you fully understand it.                */
/*                                                                           */
/*****************************************************************************/

error_bounds_t compute_error_bounds()
{
  int every_other = 1;
  double half = 0.5;
  double check = 1.0;
  double lastcheck;

  /**
   * Repeatedly divide `epsilon` by two until it is too small to add to 1.0
   * without causing roundoff.
   */
  double splitter = 1.0;
  double epsilon = 1.0;
  do {
    lastcheck = check;
    epsilon *= half;
    if (every_other)
      splitter *= 2.0;
    every_other = !every_other;
    check = 1.0 + epsilon;
  } while (!(check == 1.0 || check == lastcheck));
  splitter += 1.0;

  return (error_bounds_t) {
    .epsilon = epsilon,
    .splitter = splitter,
    .resulterrbound = (3.0 + 8.0 * epsilon) * epsilon,
    .ccwerrboundA = (3.0 + 16.0 * epsilon) * epsilon,
    .ccwerrboundB = (2.0 + 12.0 * epsilon) * epsilon,
    .ccwerrboundC = (9.0 + 64.0 * epsilon) * epsilon * epsilon,
    .o3derrboundA = (7.0 + 56.0 * epsilon) * epsilon,
    .o3derrboundB = (3.0 + 28.0 * epsilon) * epsilon,
    .o3derrboundC = (26.0 + 288.0 * epsilon) * epsilon * epsilon,
    .iccerrboundA = (10.0 + 96.0 * epsilon) * epsilon,
    .iccerrboundB = (4.0 + 48.0 * epsilon) * epsilon,
    .iccerrboundC = (44.0 + 576.0 * epsilon) * epsilon * epsilon,
    .isperrboundA = (16.0 + 224.0 * epsilon) * epsilon,
    .isperrboundB = (5.0 + 72.0 * epsilon) * epsilon,
    .isperrboundC = (71.0 + 1408.0 * epsilon) * epsilon * epsilon
  };
}


void write_error_bounds(const char * filename, error_bounds_t err_bounds)
{
  FILE * fid = fopen(filename, "w");

  fprintf(fid, "#ifndef ERROR_BOUNDS_H\n");
  fprintf(fid, "#define ERROR_BOUNDS_H\n\n");

  fprintf(fid, "/* 2^{-p}. Used to estimate roundoff errors. */\n");
  fprintf(fid, "const double epsilon = %a;\n\n", err_bounds.epsilon);

  fprintf(fid, "/* 2^ceil(p/2) + 1. Used to split floating point numbers in half. */\n");
  fprintf(fid, "const double splitter = %a;\n\n", err_bounds.splitter);

  fprintf(fid, "/* A set of constants used to calculate maximum roundoff errors. */\n");
  fprintf(fid, "const double resulterrbound = %a;\n", err_bounds.resulterrbound);

  fprintf(fid, "const double ccwerrboundA = %a;\n", err_bounds.ccwerrboundA);
  fprintf(fid, "const double ccwerrboundB = %a;\n", err_bounds.ccwerrboundB);
  fprintf(fid, "const double ccwerrboundC = %a;\n", err_bounds.ccwerrboundC);

  fprintf(fid, "const double o3derrboundA = %a;\n", err_bounds.o3derrboundA);
  fprintf(fid, "const double o3derrboundB = %a;\n", err_bounds.o3derrboundA);
  fprintf(fid, "const double o3derrboundC = %a;\n", err_bounds.o3derrboundC);

  fprintf(fid, "const double iccerrboundA = %a;\n", err_bounds.iccerrboundA);
  fprintf(fid, "const double iccerrboundB = %a;\n", err_bounds.iccerrboundB);
  fprintf(fid, "const double iccerrboundC = %a;\n", err_bounds.iccerrboundC);

  fprintf(fid, "const double isperrboundA = %a;\n", err_bounds.isperrboundA);
  fprintf(fid, "const double isperrboundB = %a;\n", err_bounds.isperrboundB);
  fprintf(fid, "const double isperrboundC = %a;\n\n", err_bounds.isperrboundC);

  fprintf(fid, "#endif\n");
  fclose(fid);
}


int main(int argc, char **argv)
{
  write_error_bounds(argv[1], compute_error_bounds());
  return 0;
}
