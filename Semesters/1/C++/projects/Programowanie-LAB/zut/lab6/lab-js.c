
#include <stdio.h>


int suma_kwadrat(int n)
{
    int a,b;
    for(a=0;a<=n;a++)
    {
        for(b=a;b<=n;b++)
        {
            if((a*a)+(b*b)==n)
            {

                printf("%d^2 + %d^2 = %d\n",a,b,n);
            }
        }
    }
}

int main(){
    suma_kwadrat(10);
    return 0;
}


int s_k(int num) {

}

/*
a = 0
b= 0 
a++
b++
5
for 
    a= 0     a = 1 a =2 a = 3 a=4
    for 
    a = 0 b= 0 
    a= 0  b= 1
    a= 0  b= 2 4 = 5
    a= 0  b= 3 9 = 5
    a= 0  b= 4 16 = 5
    a= 0  b= 5 25 = 5

    a=1 b= 0 
    a=1 b= 1
    a=1 b= 2 -> 1 + 4 
    a=1 b= 0 
    a=1 b= 0 
    -> a = 1 b=1 a^2 + b^2 
    




*/