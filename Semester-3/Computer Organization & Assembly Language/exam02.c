#include <iostream>

int main() {
    uint8_t a = 0xE3; // Example input: 1110 0011 -> Output: 1110 0110
    uint8_t y = 0;

    // Zad 2 b7b6 b5b4 b3b0 b1b2
    // 1110 0011 -> 1110 0110

    __asm {
        xor ax, ax
        xor bx, bx

        mov al, a
        shl al, 7
        shr al, 7
        shl al, 2

        add bl, al

        mov al, a
        shl al, 6
        shr al, 7
        shl al, 1

        add bl, al

        mov al, a
        shl al, 5
        shr al, 7
        shl al, 0

        add bl, al

        mov al, a
        shr al, 3
        shl al, 3
        add bl, al

        mov y, bl
    }
    printf("%#x\n", y); // Output: 0xE6 (1110 0110)
}
