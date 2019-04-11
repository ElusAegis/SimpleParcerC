#ifndef FORMULARPARCER_H
#define FORMULARPARCER_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "comm_line_input.h"

#define debug (0)
#define LOC_EPS (1e-30)

typedef double (*func_t2)(double, double);

double formularParcer(const char* stringIn, double point);

// Operation definition
double zero_f2(double x1, double x2);
double product(double x1, double x2);
double sum(double x1, double x2);
double div_reg(double x1, double x2);
double diff(double x1, double x2);
double power(double x1, double x2);
double greater(double x1, double x2);
double equal(double x1, double x2);
double less(double x1, double x2);


#endif
