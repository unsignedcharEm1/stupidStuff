#include<stdio.h>
#define rl register long
void exit(int n);
void fun();

int main() {
	fun();
	printf("I will be executed if i only return from a function\n");
	return 67;
}

// Defs
void exit(int n) {
	rl rax asm("rax") = 60;
	rl rdi asm("rdi") = n;
	asm volatile (
			"syscall"
			: // Output
			: "r" (rax), "r" (rdi) // Input
			: // "rcx", "r11", "memory" // clobber
		     );
}
void fun() {
	printf("Oh look iam a function\n");
	// exit(7); /* uncomment this and see what happens*/
	return;
}
