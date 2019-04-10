#include "comm_line_input.h"

int to_int(char *data, int *adress)
{
    char *e;
    errno = 0;

    *adress = strtol(data, &e, 10);
    if (! errno && *e == '\0')
        if (INT_MIN <= *adress && *adress <= INT_MAX)
            return 1;
    return 0;

}

int to_double(char *data, double *adress)
{
    char *e;
    errno = 0;

    *adress = strtod(data, &e);
    if (! errno && *e == '\0')
        return 1;
    return 0;
}

void print_c_i_d(struct c_i_d data)
{
    printf("\t\t");
    printf("%s", data.c);
    printf("\t\t");
    if (data.inf % 2 == 0)
        printf("%ld", data.i);
    else
        printf("--");

    printf("\t\t");

    if (data.inf % 3 == 0)
        printf("%lf", data.d);
    else
        printf("--");
    printf("\n");
}

