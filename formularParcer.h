//
// Created by Gurak on 2019-04-06.
//

#ifndef MSU_LESSONS_2SEM2019_FORMULARPARCER_H
#define MSU_LESSONS_2SEM2019_FORMULARPARCER_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "comm_line_input.h"

#define debug (1)
#define EPS (1e-30)

typedef double (*func_t2)(double, double);

double formularParcer(char* stringIn, double point);

// Operation definition
double zero_f2(double x1, double x2);
double product(double x1, double x2);
double sum(double x1, double x2);
double div_reg(double x1, double x2);
double diff(double x1, double x2);
double power(double x1, double x2);



#endif //MSU_LESSONS_2SEM2019_FORMULARPARCER_H
