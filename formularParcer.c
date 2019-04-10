#include "formularParcer.h"

double RecFormularParcer(char* stringIn, double point, int length, int* flag);
void PrepStringRecFParcer(char* stringIn, char** nStr1, char** nStr2, int length, int i);

int FuncRecongGrader(char elem, func_t2* func);
int dead_end(char* stringIn, int *flag);

int strip_spaces(const char *string, char **new_string, int* length);
char* partition(const char *stringIn, int start, int end);
int startsWith(const char *pre, const char *str);




double formularParcer(char* stringIn, double point)
{
    int length = strlen(stringIn), flag = 0;
    char *string;

    if (!strip_spaces(stringIn, &string, &length))
        return -1;

    if (debug)
        printf("No space string: %s", string);

    double answer = RecFormularParcer(string, point, length, &flag);

    if (flag)
        printf("\nCould not calculate your query: %s\n", stringIn);

    return answer;
}


int strip_spaces(const char *string, char **new_string, int* length)
{
    int c_space = 0, k = 0;

    for (int i = 0; i < *length; i++)
        if (string[i] == ' ')
            c_space++;

    *new_string = calloc(*length + 1, sizeof(char));
    if (*new_string == NULL) {
        fprintf(stderr, "Could not allocate memory");
        return 0;
    }
    (*new_string)[*length-1] = '\0';

    for (int i = 0; i < *length; i++) {
        if (string[i] != ' ')
            (*new_string)[i-k] = string[i];
        else
            k++;
    }

    *length -= c_space;
    return 1;
}


double RecFormularParcer(char* stringIn, double point, int length, int* flag)
{
    char *new_str1, *new_str2;
    int const_int, pos_prod = -1, pos_div_r = -1, pos_pow = -1, pos_x = -1;
    int pos_func = -1;
    double const_double, p1_res, p2_res;

    int temp1 = 0, temp2 = 0, temp3, ready = 0, do_abs = 0;

    func_t2 calc_func = zero_f2;

    if (debug)
        printf("\n|%s|\n", stringIn);

    // If like: sin(statement) -> sin(f(x)), same for cos(x) and ln(x)
    if (strlen(stringIn) > 4 && startsWith("sin(", stringIn) && stringIn[length - 1] == ')')
    {
        new_str1 = partition(stringIn, 4, length - 1);
        free(stringIn);

        p1_res = RecFormularParcer(new_str1, point, length - 5, flag);

        if (*flag)
            return 0;

        return sin(p1_res);
    }
    if (strlen(stringIn) > 4 && startsWith("cos(", stringIn) && stringIn[length - 1] == ')')
    {
        new_str1 = partition(stringIn, 4, length - 1);
        free(stringIn);

        p1_res = RecFormularParcer(new_str1, point, length - 5, flag);

        if (*flag)
            return 0;

        return cos(p1_res);
    }
    if (strlen(stringIn) > 3 && startsWith("ln(", stringIn) && stringIn[length - 1] == ')')
    {
        new_str1 = partition(stringIn, 3, length - 1);
        free(stringIn);

        p1_res = RecFormularParcer(new_str1, point, length - 4, flag);

        if (*flag)
            return 0;

        return log(p1_res);
    }





    // If there is a '('
    for (int i = 0; i < length; i++)
    {

        if (stringIn[i] == '(' || stringIn[i] == '|')
        {
            temp2 = i;
            temp1 = 1;
            //Checks if amount of ( and ) brackets is right

            for (int j = i + 1; temp1 && j < length; j++)
            {
                if (stringIn[i] == '(') {
                    if (stringIn[j] == '(') temp1++;
                    if (stringIn[j] == ')') {temp1--; temp2 = j;}
                } else if (stringIn[i] == '|') {
                    if (stringIn[j] == '|') {temp1--; temp2 = j; do_abs = 1;}
                }

            }

            // If empty () of ((() -> flag = 1
            if (temp1) {return dead_end(stringIn, flag);}

            if (debug)
                printf("\n%d, %d, %d- i, temp2, temp1\n", i, temp2, temp1);

            // If like: (statement) -> statement
            if (i == 0 && temp2 == length - 1)
            {
                new_str1 = partition(stringIn, 1, length - 1);
                free(stringIn);

                p1_res = RecFormularParcer(new_str1, point, length - 2, flag);

                if (*flag)
                    return 0;

                if (do_abs) p1_res = fabs(p1_res);

                return p1_res;
            }
            // if like: (statement)+statement -> f(statement, statement)
            if (i == 0) {
                if (FuncRecongGrader(stringIn[temp2 + 1], &calc_func)) {
                    new_str1 = partition(stringIn, 1, temp2);
                    new_str2 = partition(stringIn, temp2 + 2, length);
                    free(stringIn);

                    p1_res = RecFormularParcer(new_str1, point, temp2 - 1, flag);
                    if (do_abs) p1_res = fabs(p1_res);

                    p2_res = RecFormularParcer(new_str2, point, length - temp2, flag);

                    if (debug)
                        printf("\np1: %lf p2: %lf flag: %d", p1_res, p2_res, *flag);

                    if (*flag)
                        return 0;

                    return calc_func(p1_res, p2_res);
                }
//                } else return dead_end(stringIn, flag);
            }
            // if like: statement+(statement) -> f(statement, statement)
            if (temp2 == length - 1) {
                if (FuncRecongGrader(stringIn[i - 1], &calc_func)) {
                    new_str1 = partition(stringIn, 0, i - 1);
                    new_str2 = partition(stringIn, i + 1, length - 1);
                    free(stringIn);

                    p1_res = RecFormularParcer(new_str1, point, i, flag);
                    p2_res = RecFormularParcer(new_str2, point, length - i - 2, flag);
                    if (do_abs) p2_res = fabs(p2_res);

                    if (debug)
                        printf("\np1: %lf p2: %lf flag: %d", p1_res, p2_res, *flag);

                    if (*flag)
                        return 0;

                    return calc_func(p1_res, p2_res);
                }
//                } else return dead_end(stringIn, flag);
            }
            // if like statement*(statement)+statement -> f(statement*(statement), statement)
            if (FuncRecongGrader(stringIn[i - 1], &calc_func) >= FuncRecongGrader(stringIn[temp2 + 1], &calc_func) &&\
            FuncRecongGrader(stringIn[temp2 + 1], &calc_func) > 0)
            {
                pos_func = temp2 + 1; ready = 1;
            }
            // if like statement+(statement)*statement -> f(statement, (statement)*statement)
            else if (FuncRecongGrader(stringIn[temp2 + 1], &calc_func) > FuncRecongGrader(stringIn[i - 1], &calc_func) &&\
            FuncRecongGrader(stringIn[i - 1], &calc_func) > 0)
            {
                pos_func = i - 1; ready = 1;
            }
            break;
        }
    }

    // if like: statement+statement or statement*statement -> f(statement, statement)
    if (!ready) {
        temp1 = 0;
        temp2 = 0;
        for (int i = 0; i < length; i++) {

            if (stringIn[i] == '(')temp1++;
            if (stringIn[i] == ')')temp1--;
            if (temp2 && stringIn[i] == '|') temp2--;
            if (!temp2 && stringIn[i] == '|') temp2++;
            if (temp1 || temp2) continue;

            if (stringIn[i] == '+') {
                calc_func = sum;
                pos_func = i;
                ready = 1;
                break;
            }
            if (stringIn[i] == '-' && i) {
                calc_func = diff;
                pos_func = i;
                ready = 1;
                break;
            }
            if (stringIn[i] == 'x' && i && (to_int(partition(stringIn, i - 1, i), &temp3) || stringIn[i-1] == ')' || stringIn[i-1] == '|')) {
                pos_x = i;
            }
            switch (stringIn[i]) {
                case '*':
                    pos_prod = i;
                    break;
                case '/':
                    pos_div_r = i;
                    break;
                case '^':
                    pos_pow = i;
                    break;
                default:
                    break;
            }
        }
        if (!ready) {
            if (pos_prod > pos_div_r) {
                calc_func = product;
                pos_func = pos_prod;
            } else if (pos_div_r != -1) {
                calc_func = div_reg;
                pos_func = pos_div_r;
            } else if (pos_x != -1) {
                calc_func = product;

                new_str1 = partition(stringIn, 0, pos_x);
                new_str2 = partition(stringIn, pos_x, length);
                free(stringIn);

                p1_res = RecFormularParcer(new_str1, point, pos_x, flag);
                p2_res = RecFormularParcer(new_str2, point, length - pos_x, flag);

                if (debug)
                    printf("\np1: %lf p2: %lf res: %lf flag: %d", p1_res, p2_res, calc_func(p1_res, p2_res), *flag);

                if (*flag)
                    return 0;

                return calc_func(p1_res, p2_res);

            } else if (pos_pow != -1) {
                calc_func = power;
                pos_func = pos_pow;
            }
        }
    }

    if (pos_func != -1 && !(*flag))
    {
        PrepStringRecFParcer(stringIn, &new_str1, &new_str2, length, pos_func);
        p1_res = RecFormularParcer(new_str1, point, pos_func, flag);
        p2_res = RecFormularParcer(new_str2, point, length - pos_func - 1, flag);

        if (debug)
            printf("\np1: %lf p2: %lf res: %lf flag: %d", p1_res, p2_res, calc_func(p1_res, p2_res), *flag);

        if (*flag)
            return 0;

        return calc_func(p1_res, p2_res);
    }

    // If like '' -> 0 and error warning
    if (!strlen(stringIn)) {
        fprintf(stderr, "\nEncountered the '' symbol, interpret as 0!\n");
        return 0;
    }


    // If like: 123 -> int (123)
    if (to_int(stringIn, &const_int)){
        free(stringIn);
        return const_int;
    }

    // If like: 123.01 -> double (123.01)
    if (to_double(stringIn, &const_double)){
        free(stringIn);
        return const_double;
    }

    // If like: pi -> double (3.14)
    if (!strcmp(stringIn, "PI") || !strcmp(stringIn, "pi")){
        free(stringIn);
        return M_PI;
    }
    // If like: e -> double (2.71)
    if (!strcmp(stringIn, "E") || !strcmp(stringIn, "e")){
        free(stringIn);
        return M_E;
    }

    // If like: x -> double (point)
    if (strlen(stringIn) == 1 && stringIn[0] == 'x'){
        free(stringIn);
        return point;
    }

    // If none above true -> flag = 1 and return 0
    return dead_end(stringIn, flag);
}


void PrepStringRecFParcer(char* stringIn, char** nStr1, char** nStr2, int length, int i)
{
    *nStr1 = partition(stringIn, 0, i);
    *nStr2 = partition(stringIn, i + 1, length);
    free(stringIn);
}

char* partition(const char *stringIn, int start, int end)
{
    char* new_string = calloc(end - start + 2, sizeof(char));
    if (new_string == NULL) {
        fprintf(stderr, "Could not allocate memory");
        return 0;
    }
    new_string[end - start] = '\0';

    for (int i = start; i < end; i++)
        new_string[i - start] = stringIn[i];

    return new_string;
}

int double_to_int(double x, int* result)
{
    if (x - (int) x < EPS)
        *result = (int) x;

    return (x - (int) x < EPS);
}


int FuncRecongGrader(char elem, func_t2* func)
{
    switch (elem)
    {
        case '+':
            *func = sum;
            return 1;
        case '-':
            *func = diff;
            return 1;
        case '*':
            *func = product;
            return 2;
        case '/':
            *func = div_reg;
            return 2;
        case '^':
            *func = power;
            return 3;
        default:
            return 0;
    }
}

int dead_end(char* stringIn, int *flag)
{
    *flag = 1;
    if (debug)
        printf("\nThe Error in: %s\n", stringIn);

    free(stringIn);
    return 0;
}

int startsWith(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}
