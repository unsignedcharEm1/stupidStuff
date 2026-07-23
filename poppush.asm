global _start
section .data
	a dq 67 ;; make a variable named a with the type quad word (64 bits)
	b dq 420
section .text
_start:
	; save stack pointer to base pointer
	mov rbp, rsp
	; push 1
	sub rsp, 8 ;; allocate 8 bytes
	mov qword rdx, [a] ; load  the value of a into rdx register  [] is the dereference operator
	mov qword [rbp-8], rdx ;; now go into the memory location and put whatever was in rdx
	; push 2
	sub rsp, 8
	mov qword rdx, [b]
	mov qword [rbp-16], rdx
	; pop 1
	mov qword rax, [rsp] ; get whatever is in rsp and put it in rax
	add rsp, 8 ; dealloc 8 bytes
	; pop 2
	mov qword rax, [rsp]
	add rsp, 8
	mov rsp, rbp ; dealloc stack i mean this would have been useful if we had not deallocated while popping
exit:
	mov rax, 60
	mov rdi, 0
	syscall
