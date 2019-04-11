#ifndef COMMAND_LINE_INPUT_H
#define COMMAND_LINE_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

struct c_i_d
{
    char *c;
    long i;
    double d;
    int inf;
};

int to_int(char *data, int *adress);
int to_double(char *data, double *adress);

void print_c_i_d(struct c_i_d data);
#endif //MSU_LESSONS_2SEM2019_COMMAND_LINE_INPUT_H



