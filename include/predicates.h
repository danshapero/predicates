
#ifndef PREDICATES_H
#define PREDICATES_H

/* Geometric predicates */
double orient2d(double * pa, double * pb, double * pc);
double orient3d(double * pa, double * pb, double * pc, double * pd);

double incircle(double * pa, double * pb, double * pc, double * pd);
double insphere(double * pa,
                double * pb,
                double * pc,
                double * pd,
                double * pe);


/* Fast but non-robust geometric predicates */
double orient2dfast(double * pa, double * pb, double * pc);
double orient3dfast(double * pa, double * pb, double * pc, double * pd);

double incirclefast(double * pa, double * pb, double * pc, double * pd);
double inspherefast(double * pa,
                    double * pb,
                    double * pc,
                    double * pd,
                    double * pe);

#endif
