#include <stdio.h>
#include "color.h"

#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define BLACK "\033[0m"

void red()
{
    printf(RED);
}

void yellow()
{
    printf(YELLOW);
}

void reset()
{
    printf(BLACK);
}