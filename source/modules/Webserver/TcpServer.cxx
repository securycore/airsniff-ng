#include "Exceptions.hxx"
#include "TcpConnection.hxx"
#include "TcpServer.hxx"

#include <cstdlib>

using namespace komancs;

TcpServer::TcpServer(const char *ip, int port, int backlog = 10)
    : m_addressIsOwn(true)
{
    m_address = new Ipv4Address(ip, port);
    if ((m_fd = ::socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw error::SystemException("socket()");
    bind();
    listen(backlog);
}

TcpServer::TcpServer(HostType type, int port)
    : m_addressIsOwn(true)
{
    m_address = new Ipv4Address(type, port);
    if ((m_fd = ::socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw error::SystemException("socket()");
    bind();
    listen(10);
}

TcpServer::TcpServer(Ipv4Address *addr)
    : m_addressIsOwn(false), m_address(addr)
{
    if ((m_fd = ::socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw error::SystemException("socket()");
    bind();
    listen(110);
}

TcpServer::~TcpServer()
{
    ::shutdown(m_fd, SHUT_RDWR);
    if (m_addressIsOwn)
        delete m_address;
}

void TcpServer::bind()
{
    int yes = 1;

    /* Get rid from "the socket is already in use" message */
    if (::setsockopt(m_fd, SOL_SOCKET
        , SO_REUSEADDR, &yes, sizeof(int)) == -1) 
        throw error::SystemException("setsockopt()");


    if (::bind(m_fd, (struct sockaddr *)m_address->addressPointer()
        , m_address->size()) == -1)
        throw error::SystemException("bind()");
}

void TcpServer::listen(int backlog = 10)
{	
	if (::listen(m_fd, backlog) == -1) 
        throw error::SystemException("listen()");
}

TcpConnection *TcpServer::accept()
{
    int socket;
    struct sockaddr_in clientAddr; 
    socklen_t sin_size = sizeof(struct sockaddr_in);
	if ((socket = ::accept(m_fd
        , (struct sockaddr *)&clientAddr, &sin_size)) == -1)
        throw error::SystemException("accept()");

    return new TcpConnection(socket);
}
