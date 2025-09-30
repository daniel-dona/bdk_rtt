#include <stdint.h>
#define USE_SEC_TEST_CMD 0

extern int hal_sha256_self_test( int  );

extern void *aes_encrypt_init(const uint8_t *key, size_t len);
extern void aes_encrypt(void *ctx, const uint8_t *plain, uint8_t *crypt);
extern void aes_encrypt_deinit(void *ctx);
extern void *aes_decrypt_init(const uint8_t *key, size_t len);
extern void aes_decrypt(void *ctx, const uint8_t *crypt, uint8_t *plain);
extern void aes_decrypt_deinit(void *ctx);
