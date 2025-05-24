#include <stdio.h>;

// Ex. 1a)
int main() 
{
    unsigned char a = 15;
    unsigned short y;
    y = (unsigned short)(a << 4) + (unsigned short)(a << 2);
// to support >8 bit number, we would shift al/bl but as a result 8bit would be the definite max
// which is not what we should be doing
    _asm {
    	xor eax, eax
    	xor ebx, ebx
    	mov al, a
    	shl ax, 4
    	mov bl, a
    	shl bx, 2
    	add ax, bx
    	mov y, ax
    }

    printf("%d", y);
}
