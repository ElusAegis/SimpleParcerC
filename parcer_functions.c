#include "formularParcer.h"

double zero_f2(double x1, double x2)
{
    return 0;
}

double sum(double x1, double x2)
{
    return x1 + x2;
}

double product(double x1, double x2)
{
    printf("\n%lf %lf\n ", x1, x2);
    return x1 * x2;
}

double diff(double x1, double x2)
{
    return x1 - x2;
}

double div_reg(double x1, double x2)
{
    return x1 / x2;
}

double power(double x1, double x2)
{

    return powf(x1, x2);
}

double abs_r(double x1)
{
    return fabs(x1);
}

//double remainder(int x1, int x2)
//{
//    return x1 % x2;
//}
