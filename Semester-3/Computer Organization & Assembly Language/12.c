// Author: folate
// Edited: jirafey
// Ex. 12
#include <stdio.h>;

int main() {
    int y = 0;
    for (int i = 0; i < 5; i++) y += i;
    printf("%d\n", y);
    unsigned int c = 0;
    __asm {
        mov eax, c
        mov ebx, 0
        mov ecx, 0
        startt:
        sub ecx, 5
            jnc eend
            add ebx, 1
            mov ecx, ebx
            add eax, ecx
            jmp startt
            eend :
        sub eax, ebx
            mov c, eax
    }

    printf("12: %d\n\n", c);
}
