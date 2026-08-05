#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
// Type definitions
typedef struct charBit {
	uint32_t b;
} charBit;

// Object functions

charBit * makeCharBit() {
	charBit *p = malloc(sizeof(charBit));
	p->b ^= p->b; // A xor A = 0
	return p;
}
void deleteCharBit(charBit *p) {
	free(p);
}
// Operations
void charIntoBit(charBit *p, char *string) {
	uint8_t SHIFT = 0;
	for (uint8_t i = 0; string[i] != '\0'; i++) {
		SHIFT += 8;
		p->b = (p->b) | ( (uint32_t) (string[i]) << 32-SHIFT);
	}
}

char* charOutBit(charBit *p) {
	static char string[5]; string[4] = '\0';
	uint8_t SHIFT = 0;
	for (uint8_t i = 0; i < 4; i++) {
		SHIFT += 8;
		string[i] = ((p->b) >> 32-SHIFT) & 0xFF; // 1 hex digit = 4 bit so 2 hex digit is 8 bits
	}
	return string;
}

int main() {
	charBit *p = makeCharBit();
	charIntoBit(p, "meow");
	printf("%s\n", charOutBit(p));
	deleteCharBit(p);
}
