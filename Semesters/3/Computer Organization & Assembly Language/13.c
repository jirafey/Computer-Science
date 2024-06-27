// Author: folate
// Ex. 13
#include <stdio.h>;

int main() {
    typedef union {
        unsigned char BYTE;
        struct {
            unsigned char a : 2;
            unsigned char b : 3;
            unsigned char c : 3;
        }bits;
    }un_X;

    un_X x;
    x.bits.a = 1;
    x.bits.b = 2;
    x.bits.c = 1;

    unsigned char a = x.BYTE & 0b00000011;
    unsigned char b = (x.BYTE & 0b00011100) >> 2;
    unsigned char c = (x.BYTE & 0b11100000) >> 5;

    if (c == 1) a = b;
    x.BYTE = 0;
    x.BYTE = x.BYTE | a;
    x.BYTE = x.BYTE | b << 2;
    x.BYTE = x.BYTE | c << 5;

    printf("13 C: %d\n\n", x.BYTE);
    __asm {
        mov al, x.BYTE
        and al, 0x03
        shr al, 0

        mov bl, x.BYTE
        and bl, 0x1C
        shr bl, 2

        mov cl, x.BYTE
        and cl, 0xE0
        shr cl, 5

        // porownanie
        cmp cl, 0x01
        jnz end // jezeli c!==1 to skip
        // jezeli c==1 to a=b
        mov al, bl
        end :
        mov dl, 0
            // przypisanie do x.BYTE wynikow
            and al, 0x03
            shl al, 0
            or dl, al
            and bl, 0x07
            shl bl, 2
            or dl, bl
            and cl, 0x07
            shl cl, 5
            or dl, cl
            mov x.BYTE, dl
    }

    printf("13 ASM: %d\n\n", x.BYTE);
}
