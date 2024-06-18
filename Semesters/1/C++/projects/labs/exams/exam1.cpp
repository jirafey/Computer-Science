#include <iostream>

using namespace std;

int zad1(int a, int b, int c)
{
    int max_num = max(a, max(b, c));
    int min_num = min(a, min(b, c));

    int middle = 0;
    if (a > b)
    { // 7 80 2
        if (b > c)
        {
            middle = b;
        }
        else if (c > a)
        {
            middle = a;
        }
        else
        {
            middle = c;
        }
    }
    else
    {
        if (b < c)
        {
            middle = a;
        } // 1 5 2

        else if (c < a)
        {
            middle = a;
        }
        else
        {
            middle = c;
        }
    }
    printf("%d\n%d\n%d\n", max_num, middle, min_num);
}