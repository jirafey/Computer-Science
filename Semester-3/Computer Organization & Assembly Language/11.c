// Ex. 11
#include <stdio.h>;

int main()
{
    short y = 0;
    short a = 1000;
    //y=1.125*a
    y = (a << 0) + (a >> 3);
    printf("11 C: %d\n", y);
    y = 0;
    _asm {
        mov ax, y
        mov bx, a

        shr bx, 0
        add ax,bx
  
        shr bx, 3
        add ax,bx

        mov y, ax
    }
    printf("11 asm: %d\n", y);
}
