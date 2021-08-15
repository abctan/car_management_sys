#include "common.h"
#include <stdlib.h>
#include <time.h>

int com_rand(int min, int max, int *value)
{
    static unsigned int i = 0;
    ERRP(value == NULL, "com_rand param is null!", goto ERR0);
    ERRP(min >= max, "min >= max", goto ERR0);
    ERRP(max > RAND_MAX, "max > RAND_MAX", goto ERR0);

    srand(time(NULL) + (i++));
    *value = (rand() % ((max - min) + 1)) + min;

    return SUCCESS;
ERR0:
    return FAILURE;
}