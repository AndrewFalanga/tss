
#ifndef _NPM_CRYPTO_H_
#define _NPM_CRYPTO_H_

#include <cerrno>
#include <cstdint>
#include <stdint.h>

struct _NpmCrypto {
    int (*Sign)(struct _NpmCrypto*, const uint8_t*, uint32_t, uint8_t[104]);
    int (*Verify)(struct _NpmCrypto*, const uint8_t*, uint32_t, const uint8_t[104]);
    void (*Clean)(void);
};

typedef struct _NpmCrypto NpmCrypto;

void DestroyCrypto(NpmCrypto**);

/*
 * Convenience methods
 */

/**
 * Sign (NpmSign)
 * Sign the provided data buffer using ECC with curve P-384 and SHA384
 *
 * @param cr The NpmCrypto object owning the keys
 * @param data The data buffer to sign
 * @param dataLength The length of the data in bytes
 * @param signature The array into which the DER formatted ECC signature will be
 * placed. The array is 104 bytes in length to accommodate the DER structure and
 * the (r,s) points of the signature. It may be less but will be no more.
 *
 * @return 0 Success
 * @return EINVAL cr or data are NULL; or dataLength is 0
 * @return ERRNO, or other codes, from underlying crypto implementation
 */
static int NpmSign(NpmCrypto* cr, const uint8_t* data, uint32_t dataLength, uint8_t signature[104])
{
    if (cr) return cr->Sign(cr, data, dataLength, signature);
    else return EINVAL;
}

/**
 * Verify (NpmVerify)
 * Verify the supplied data buffer with the provided signature.
 *
 * @param cr The NpmCrypto object owning the keys
 * @param data The data to verify
 * @param dataLength The length of the data in bytes
 * @param signature The DER formatted signature expected from the data using ECC
 * P-384 and SHA384
 *
 * @return 0 Success (or authentic)
 * @return EINVAL cr or data are NULL; dataLength is 0
 * @return ERRNO or other errors from cryptographic implementation
 */
static int NpmVerify(NpmCrypto* cr, const uint8_t* data, uint32_t dataLength, const uint8_t signature[104])
{
    if (cr) return cr->Verify(cr, data, dataLength, signature);
    else return EINVAL;
}


#endif
