global _start
section .bss
	buf resb 20
section .text
_start:
	mov rax, 67676767
	call print_udiv
	jmp exit
print_udiv:
	lea rsi, [buf+19]
	mov byte [rsi], 0x0a
	mov rbx, 10
.next:
	dec rsi
	xor rdx, rdx
	div rbx
	add rdx, '0'
	mov byte [rsi], dl
	test rax, rax
	jnz .next
	lea rdx, [buf+20]
	sub rdx, rsi
	; print
	mov rax, 1
	mov rdi, 1
	syscall
	ret
exit:
	mov rax, 60
	mov rdi, 0
	syscall
