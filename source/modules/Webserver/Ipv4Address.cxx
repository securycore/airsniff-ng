#include "Ipv4Address.hxx"
#include "Exceptions.hxx"

#include <cstdlib>
#include <cstring>

using namespace komancs;

Ipv4Address::Ipv4Address(const Ipv4Address &addr)
{
    m_address = addr.address();
}

Ipv4Address::Ipv4Address(const struct ::sockaddr_in &addr)
{
    setAddress(addr);
}

Ipv4Address::Ipv4Address(HostType type, int port)
{
    init();
    setPort(port);
    setHostType(type);
}

Ipv4Address::Ipv4Address(const char *ip, int port)
{
    init();
    setPort(port);
    setAddress(ip);
}

void Ipv4Address::setPort(int port)
{
    if (port > 65536 || port < 0) 
        throw error::InvalidPortNumber(port);

    m_address.sin_port = htons(port);
}

void Ipv4Address::setAddress(const char *ip)
{
    if (ip != NULL)
        m_address.sin_addr.s_addr = ::inet_addr(ip);
}

void Ipv4Address::setAddress(const struct ::sockaddr_in &addr)
{
    m_address = addr;
}

Ipv4Address &Ipv4Address::operator =(const Ipv4Address &addr)
{
    m_address = addr.address(); 
    return *this;
}

bool Ipv4Address::operator ==(const Ipv4Address &addr)
{
    ::sockaddr_in sock = addr.address();
    return m_address.sin_addr.s_addr == sock.sin_addr.s_addr;
}

void Ipv4Address::init()
{
    m_address.sin_family = AF_INET;
    std::memset(&(m_address.sin_zero), 0, 8);
}

void Ipv4Address::setHostType(HostType type)
{
    m_address.sin_addr.s_addr = htonl(type);
}
