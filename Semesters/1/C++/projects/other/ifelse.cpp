#include <iostream>

using namespace std;

void main()
{
    // can omit curly braces
    int a = 10;
    if (a> 10)
    a = 2*a;
    if (a >5){
        printf("1");
        

    }else if (a=4){
        printf("@");
    }else{
        printf("2");
    }
    switch (a)
    {
    case 1:
        printf("1");
        break;
    
    default:
    printf("else");
        break;
    }

}