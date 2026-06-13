

#ifndef _NPM_STREAM_H_
#define _NPM_STREAM_H_

#include <cerrno>
#include <stdint.h>

struct _NpmStream {
    int (*Send)(struct _NpmStream*, uint8_t *data, uint32_t dataLength);
    int (*Recv)(struct _NpmStream*, uint8_t *data, uint32_t *dataLength);
};

typedef struct _NpmStream NpmStream;

void DestroyNpmStream(NpmStream** st);

/*
 * Convenience methods
 */

/**
 * Send data over the stream
 *
 * @param st The object owning the stream to use
 * @param data The buffer of data to send
 * @param dataLength The length in bytes of the buffer
 *
 * @return 0 Success
 * @return EINVAL st or data are NULL or dataLength is 0
 * @return ERRNO from implementation
 */
static int SendToStream(NpmStream *st, uint8_t *data, uint32_t dataLength)
{
    if (st) return st->Send(st, data, dataLength);
    else return EINVAL;
}

/**
 * Receive from the stream
 *
 * @param st The object owning the stream with the data
 * @param data The buffer into which received data will be placed
 * @param dataLength The length, in bytes, of that buffer
 *
 * @return 0 Success (in the case that no errors were present, but nothing was
 * received, check that dataLength == 0)
 * @return EINVAL st or data are NULL; dataLength is NULL
 * @return ERRNO from underlying OS or libraries
 */
static int RecvFromStream(NpmStream *st, uint8_t *data, uint32_t *dataLength)
{
    if (st) return st->Recv(st, data, dataLength);
    else return EINVAL;
}

#endif
