// Author: folate
// Ex. 14
#include <stdio.h>;

int main() {
    typedef union {
        unsigned char BYTE;
        struct {
            unsigned char a : 1;
            unsigned char b : 3;
            unsigned char c : 4;
        }bits;
    }un_K;

    un_K m;
    m.bits.a = 1;
    m.bits.b = 5;
    m.bits.c = 9;
    
    // insert the number on the "1" bits
    unsigned char a = m.BYTE & 0b00000001; 
    unsigned char b = (m.BYTE & 0b00001110) >> 1;
    unsigned char c = (m.BYTE & 0b11110000) >> 4;
    
    c = a * b;
    
    // Combine the bits into the whole
    m.BYTE = 0;
    m.BYTE = m.BYTE | a;
    m.BYTE = m.BYTE | b << 1;
    m.BYTE = m.BYTE | c << 4;

    printf("14 C: %d\n\n", m.BYTE);
    
    // Reset for the assembly solution
    m.bits.a = 1;
    m.bits.b = 5;
    m.bits.c = 9;

    __asm {
        mov al, m.BYTE
        and al, 0x01 // 0000 0001

        mov bl, m.BYTE
        and bl, 0x0E // 0000 1110
        shr bl, 1

        mov cl, m.BYTE
        and cl, 0xF0 // 1111 0000
        shr cl, 4

        mov ah, bl // ax = al_bl
        mov ch, 0 // cx = 0000_0000_cl
        multi:
            add ch, al
            dec ah // (al)

            jz end // if ah = 0 -> end
            jmp multi // loop
            end :
        mov cl, ch

            mov dl, 0

            and al, 0x01 // make content 0x01
            or dl, al

            and bl, 0x07 // make content 0x07
            shl bl, 1
            or dl, bl

            and cl, 0x0F // make content 0x0F
            shl cl, 4
            or dl, cl
            mov m.BYTE, dl
    }

    printf("14 ASM: %d\n\n", m.BYTE);
}
