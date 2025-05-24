// Author: folate
// Edited: Jirafey
// Ex. 14

#include <stdio.h>;

int main() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 2;
			unsigned char b : 4;
			unsigned char c : 2;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 1; // ccbb bb01
	x.bits.b = 2; // cc00 10aa
	x.bits.c = 3; // 11bb bbaa
	
	// inserting "1" in the defined bits length for variables a, b, c
	unsigned char a = (x.BYTE & 0b00000011) >> 0; 
	unsigned char b = (x.BYTE & 0b00111100) >> 2;
	unsigned char c = (x.BYTE & 0b11000000) >> 6;

	c = a * b; // 1*2 = 2 -> 10bb bbaa

	x.BYTE = 0;

	x.BYTE = x.BYTE | a << 0; // 0000 00[01]
	x.BYTE = x.BYTE | b << 2; // 00[00 10]01
	x.BYTE = x.BYTE | c << 6; // [10]00 1001 = 128 + 8 + 1 = 137

	printf("14 C: %d\n", x.BYTE);

	x.bits.a = 1; // ccbb bb01
	x.bits.b = 2; // cc00 10aa
	x.bits.c = 3; // 11bb bbaa

	__asm {
		// the same like in C
		mov al, x.BYTE
		and al, 0x01 // 0000 0001

		mov bl, x.BYTE
		and bl, 0x08 // 0000 1000
		shr bl, 2

		mov cl, x.BYTE
		and cl, 0xC0 // 1100 0000
		shr cl, 6

		mov ah, bl // ax = bl_al
		mov ch, 0 // cx = 0000_0000_cl

		add_loop:
			add ch, al // cx = al_cl 
			dec ah // bl--

			jz stop // if bl = 0 -> stop
			jmp add_loop // otherwise continue the loop
		stop:
			mov cl, ch // move the result to cl

			mov dl, 0 
			// the same like in C
			and al, 0x03 // ccbb bb11 -> 11 -> 3 -> 0x03
			or dl, al // insert values by or

			and bl, 0x0F // cc11 11aa -> 1111 -> 15 -> 0x0F
			shl bl, 2 
			or dl, bl // insert values by or

			and cl, 0x03 // 11bb bbaa -> 11 -> 3-> 0x03
			shl cl, 6 
			or dl, cl// insert values by or

			mov x.BYTE, dl

	}
	printf("14 ASM: %d\n", x.BYTE);

}
