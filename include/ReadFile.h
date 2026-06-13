

#ifndef _READ_FILE_H_
#define _READ_FILE_H_

#include <stdint.h>

/**
 * Read the contents of a file into allocated memory
 *
 * The function takes the supplied file name, opens it using the POSIX
 * file functions and places the contents into the pointer supplied.
 * The file's size is determined and the memory allocated. The contents
 * are read, in binary form, and placed into the allocated buffer. It
 * is the caller's responsibility to free that buffer.
 *
 * @param file An ASCII string denoting the file's name
 * @param contents A pointer to a pointer in which heap allocated memory
 *        will be placed along with the contents of the file.
 * @param size A pointer to a location wherein to store the file's size
 *
 * @return 0 Success
 * @return EINVAL file, contents or size are NULL
 * @return EINVAL *contents is NOT NULL
 * @return ERRNO values as returned from library and system calls
 */
int ReadFile(const char* file, void **contents, uint32_t *size);

#endif
