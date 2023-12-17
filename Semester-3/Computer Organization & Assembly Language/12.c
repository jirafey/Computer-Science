#include <stdio.h>;

int main() {
unsigned int c = 0;
unsigned int k = 0;
__asm {
    mov eax, c
    mov ebx, 0
    mov ecx, 0
    startt:
        sub ecx, 0x00000008
        jnc eend
        add ebx, 1
        mov ecx, ebx
        add eax, ecx
        jmp startt
    eend:
        sub eax, ebx
        mov c, eax
}
printf("12: %d\n\n", c);
}
