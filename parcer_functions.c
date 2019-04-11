#include "formularParcer.h"

double zero_f2(double x1, double x2)
{
    return 0 * (x1 + x2);
}

double sum(double x1, double x2)
{
    return x1 + x2;
}

double product(double x1, double x2)
{
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

double greater(double x1, double x2)
{
    return x1 < x2;
}

double less(double x1, double x2)
{
    return greater(x2, x1);
}

double equal(double x1, double x2)
{
    return (x1 - x2) < LOC_EPS;
}

//double remainder(int x1, int x2)
//{
//    return x1 % x2;
//}
