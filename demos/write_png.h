
#ifndef WRITE_PNG_H
#define WRITE_PNG_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

int matrix_to_png(const char * filename,
                  const size_t nx,
                  const size_t ny,
                  const double * A);

#ifdef __cplusplus
}
#endif

#endif
