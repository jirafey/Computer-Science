#include <iostream>
using namespace std;

int main()
{
    typedef union {
        unsigned char BYTE;
        struct {
            unsigned char a : 2;
            unsigned char b : 2;
            unsigned char c : 4;
        }bits;
    }un_K;
    un_K x;

    x.bits.a = 3;
    x.bits.b = 3;
    x.bits.c = 9;

    char a = (x.BYTE & 0b00000011);
    char b = (x.BYTE & 0b00001100) >> 2;
    char c = (x.BYTE & 0b11110000) >> 4;

    c = a * b;

    printf("c = %d\n", c);
}
