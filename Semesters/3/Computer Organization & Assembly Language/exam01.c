#include <iostream>

int main() {
    uint8_t a = 100;
    uint16_t y = 0;

    __asm {
        xor ax, ax
        add al, a
        
        add ax,ax
        add ax,ax
        add ax,ax
        add ax,ax

        mov bx, ax

        add ax, bx
        add ax, bx
        add ax, bx
        add ax, bx

        mov y, ax
    }

    printf("%d", y);
}
