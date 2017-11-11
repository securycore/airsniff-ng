#ifndef TCP_SERVER_HXX
#define TCP_SERVER_HXX

#include "InetGlobals.hxx"
#include "Ipv4Address.hxx"

namespace komancs
{
    class TcpConnection;

    class TcpServer
    {
    public:
        TcpServer(const char *, int, int);
        TcpServer(HostType, int);
        TcpServer(Ipv4Address *);
        ~TcpServer();
//      void setPort(int);
        TcpConnection *accept();

    private:
        TcpServer(const TcpServer &);
        TcpServer &operator =(const TcpServer &);
        void listen(int);
        void bind();

        int m_fd;
        bool m_addressIsOwn;
        Ipv4Address *m_address;
    };
}

#endif // TCP_SERVER_HXX
