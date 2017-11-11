#include "Exceptions.hxx"
#include "InetGlobals.hxx"
#include "TcpConnection.hxx"

#include <cstring>

using namespace komancs;

TcpConnection::TcpConnection(int fd)
    :m_clientFd(fd) { }

void TcpConnection::send(const char *str)
{
    send((const void *)str, strlen(str));
}

void TcpConnection::send(const void *data, int len)
{
    if (::send(m_clientFd, data, len, 0) == -1)
        throw new error::Exception("send");
}

template <class Iter>
void TcpConnection::send(Iter &begin, Iter &end)
{
    for (Iter it = begin; it != end; it++) {
        send(reinterpret_cast<void *>(&(*it)), sizeof(*it));
    }
}

void TcpConnection::receive(char *buffer, int len)
{
    len--;
    if (len < 0 || buffer == 0)
        throw new error::Exception("receive");

    std::memset((char *)buffer, 0, (size_t)len);
    if (::recv(m_clientFd, (void *)buffer, (size_t)len, 0) == -1)
            throw new error::Exception("receive");

    buffer[len] = '\0';
}

void TcpConnection::shutdown(enum How h)
{
    ::shutdown(m_clientFd, ShutReadWrite);
}
