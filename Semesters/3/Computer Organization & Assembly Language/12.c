// Ex. 12
#include <stdio.h>;

int main()
{
    int y = 0;
    for (int i = 0; i < 5; i++) y += i;
    printf("12 C: %d\n", y);
    y = 0;
    _asm {
        
        mov eax, 0
    loop_start:
        sub eax, 5
        jnc loop_end
        add eax, 5
        add y, eax
        add eax, 1
        jmp loop_start
    loop_end:
    }
    printf("12 asm: %d\n", y);
}
