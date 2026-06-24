#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
// Quantum Number Generator
/*
   n --> Principal orbit number
   l --> Orbital number : [0, n-1]
   m --> Magnetic number : [-l, l]
   s --> Spin Number : + 1/2 , -1/2 per m
*/

// Print Header func
void header(int n, char c) {
	for (int i = 0; i < n; i++) putchar(c);
	putchar('\n');
}

// Orbital mapping
int chIndex(uint8_t c) {
	int index = -1;
	const uint8_t *map = "spdf";
	for (int i = 0; map[i] != '\0'; i++)
		if (map[i] == c) {
			index = i; break;
		}
	return index;
}

// Generator Functions

int gen_l (int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d", i);
		if (i != n-1) printf(", ");
	}
	putchar('\n');
	return i;
}
int gen_m(int l) {
	int i, ctr = 0;
	for (i = -l; i <= l; i++) {
		printf("%d", i);
		if (i != l) printf(", "); ctr++;
	}
	putchar('\n');
	return ctr;
}
int gen_s(int m) {
	printf("%d plus minus (1/2)\n", m);
	return m;
}

int gen_n(int n) {
	int buf;
	printf("n = %d\n", n);

	printf("l = ");
	buf = gen_l(n);

	printf("m = ");
	buf = gen_m(buf);

	printf("s = ");
	buf = gen_s(buf);
}
// Specifier mode
int spec_gen(int n, int l) {
	int buf;
	printf("n = %d\n", n);
	printf("l = %d\n", l);

	printf("m = ");
	buf = gen_m(l);

	printf("s = ");
	buf = gen_s(buf);
}

// Main
int main() {
	int buf; // Int buffer
	char cbuf[10]; // Char buffer

	// Main event loop
	while (1) {
	printf("Select Mode:\n[0] possible n\n[1] Specifier mode: n and l\n ctrl + c to exit\n");
	header(4, '-');
	do {
	scanf("%d", &buf);
	if (buf > 1 || buf < 0) printf("Invalid Choice\n");
	} while (buf > 1 || buf < 0);
	switch (buf) {
		case 0:
			scanf("%d", &buf);
			gen_n(buf);
			header(4, '-');
			break;
		case 1:
			scanf("%s", &cbuf);
			// We are gonna do a evil hack
			buf = chIndex(cbuf[strlen(cbuf)-1]);
			cbuf[strlen(cbuf)-1] = '\0';
			// what just happened wtf????
			spec_gen(atoi(cbuf), buf);
			header(4, '-');
			break;
		}
	}
	return 0;
}
