#undef printf
void printf(char *s) {
	long i = 0;
	while (s[i] != '\0') ++i;
	__asm__ volatile (
		"movq $1, %%rax\n\t" 
		"movq $1, %%rdi\n\t"
		"movq %0, %%rsi\n\t"
		"movq %1, %%rdx\n\t" // since our string length is 5 we load it into rdx
		"syscall"
		: // output
		: "r" (s), "r" (i) // input
		: "rcx", "r11", "rax", "rdi", "rsi", "rdx" // In linux when we do a syscall it explicitly modifies "rcx" and "r11" register and the rest of the registers are what we modified
	);
}
int main() {
	printf("i have invented printf\n");
}
