
#ifndef PREDICATES_H
#define PREDICATES_H

/**
 * Robust, adaptive-precision geometric predicates
 */

double orient2d(const double * pa, const double * pb, const double * pc);
double orient3d(const double * pa,
                const double * pb,
                const double * pc,
                const double * pd);

double incircle(const double * pa,
                const double * pb,
                const double * pc,
                const double * pd);
double insphere(const double * pa,
                const double * pb,
                const double * pc,
                const double * pd,
                const double * pe);


/**
 * Nonrobust, fast geometric predicates.
 */

double orient2dfast(const double * pa, const double * pb, const double * pc);
double orient3dfast(const double * pa,
                    const double * pb,
                    const double * pc,
                    const double * pd);

double incirclefast(const double * pa,
                    const double * pb,
                    const double * pc,
                    const double * pd);
double inspherefast(const double * pa,
                    const double * pb,
                    const double * pc,
                    const double * pd,
                    const double * pe);


/**
 * Routines for stress-testing geometric predicates.
 * These are used in both unit tests and demo programs.
 */

typedef double (*orient2d_t)(const double *, const double *, const double *);

/**
 * Parameters:
 *    orientation: which geometric predicate to test; this must be either the
 *      address of `orient2d` or `orient2dfast`
 *    points: an array of the points around which we will be perturbing the
 *      inputs; a length-3 array of double[2]
 *    index: which input point to perturb; either 0, 1, 2
 *    grid_size: number of pixels along each dimension
 * Returns:
 *   zs: a heap-allocated (ny, nx)-array in row-major order of the orientations
 *     of all the perturbed inputs relative to the non-perturbed inputs.
 *     User is reponsible for destruction of this array.
 */
double * perturb_orient2d(const orient2d_t orientation,
                          const double ** points,
                          const size_t index,
                          const size_t grid_size);

#endif
