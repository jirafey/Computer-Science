// Author: folate
// Ex.2
#include <stdio.h>;

int main() {
unsigned char e = 0x33;
unsigned char b;
__asm {
    mov al, e
    cmp al, 0x32
    jnz endif
        mov b, 0
        jmp end
    endif:
        mov b, 1
    end:
}

printf("2: %d\n\n", b);
}
