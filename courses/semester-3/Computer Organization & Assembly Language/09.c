// Ex. 9
#include <stdio.h>

int main()
{
    unsigned char a = 3;   // 8-bit
    unsigned char b = 6;   // 8-bit
    unsigned short y = 0;  // 16-bit

    for (int i = 1; i <= b; i++) {
        y += a;
    }
    printf("9 C: %d\n", y);

    y = 0;

    __asm {
        xor ax,ax
        xor bx,bx
        xor cx,cx
        mov bl, b
        mov cl, a
        loop_start :
        sub ax, bx
            jnc loop_end
            add ax, bx
            add y, cx
            add ax, 1
            jmp loop_start
            loop_end :
    }
    printf("9 asm: %d\n", y);
}
