#include "tss_socket.h"
#include "tss_common.h"

#include <cstdio>
#include <exception>
#include <sys/socket.h>

TssSocket::TssSocket(std::string foreign)
    : _fd(0)
{
    _fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (0 > _fd)
        throw std::runtime_error(strerror(errno));
}

TssSocket::operator int() const
{
    return GetFd();
}

int TssSocket::GetFd() const
{
    return _fd;
}

int TssSocket::send(Message)
{
    return 0;
}

Message TssSocket::recv()
{
    return Message::Hello;
}
