global _start ; declare to the linker that the _start symbol exists
section .bss 
	buf resb 20 ; reserve 20 bytes at runtime 
section .text
_start:
	mov rax, 67676767 ; we are gonna put something into rax register to print
	call print_udiv 
	jmp exit
print_udiv:
	lea rsi, [buf+19] ; go to the end of the buffer
	mov byte [rsi], 0x0a ; and put a '\n'
	mov rbx, 10 ; now we are gonna convert the value in rax into ascii so we prepare to divide by 10
.next:
	dec rsi ; move the pointer to the buffer to the left by 1
	xor rdx, rdx ; clear rdx into 0
	div rbx ; divide rax by rbx and the remainder is stored in rdx
	add rdx, '0' ; now we just add the ascii value of '0' to convert it into ascii
	mov byte [rsi], dl ; since ascii doesnt go over 8 bit we just use the 8 bit version of the register and put it in the buffer
	test rax, rax ; check if rax is equal to 0 by doing an AND operation on it self
	jnz .next ; if our test statement is not zero then repeat this whole process
	lea rdx, [buf+20] ; now we are gonna calculate the length of our string by going to the end of buf + 1 and then
	sub rdx, rsi ; since rsi has reached the start of the buffer we can just subtract it from rdx
	; print
	mov rax, 1
	mov rdi, 1
	syscall
	ret
exit:
	mov rax, 60
	mov rdi, 0
	syscall
