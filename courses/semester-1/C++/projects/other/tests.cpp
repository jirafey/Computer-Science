#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int RNG()
{

    return (rand() % (10 - 9 + 1)) + 9;
}
int RNG2(int lower, int upper)
{

    return (rand() % (upper - lower + 1)) + lower;
}
int main()
{
    srand(time((time_t *)0));
    printf("%d", RNG());
    return 0;
}
