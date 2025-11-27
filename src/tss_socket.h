#pragma once

#include "tss_common.h"
#include <string>

/*
 * Sockets class. This class implements UDP type sockets which are used by this
 * program. This is not a generic implementation of sockets.
 *
 */

class TssSocket {
    int _fd;

    TssSocket();
    public:
    TssSocket(std::string foreign);

    int send(Message);
    Message recv();

    int GetFd() const;

    /* for intuitive use in the select() function */
    operator int() const;
};
