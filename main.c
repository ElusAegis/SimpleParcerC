#include "formularParcer.h"
#include <stdio.h>

char *(link[100]);

double calc(double point)
{
    return formularParcer(*link, point);
}

int main() {
    double point = 1;
    double (*func) (double);
    func = calc;

    char string[100];
    scanf("%s", string);
    scanf("%lf", &point);
    *link = string;
//    double (*formular)(double) = formularParcer(string);
//    printf("%lf", formular(1));
    printf("\n\n%lf", func(point));
}
