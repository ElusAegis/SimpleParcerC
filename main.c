#include "formularParcer.h"
#include <stdio.h>

int main() {
    double point = 1;
    char *string;
    scanf("%s", string);
    scanf("%lf", &point);
//    double (*formular)(double) = formularParcer(string);
//    printf("%lf", formular(1));
    printf("\n\n%lf", formularParcer(string, point));
}
