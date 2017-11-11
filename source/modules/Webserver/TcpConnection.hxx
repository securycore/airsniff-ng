#ifndef TCP_CONNECTION_HXX
#define TCP_CONNECTION_HXX

#include <string>
#include <vector>

namespace komancs {
    class TcpConnection
    {
    public:
        enum How { ShutRead, ShutWrite, ShutReadWrite };
        TcpConnection(int);
        ~TcpConnection() { shutdown(); }

        void send(const char *);
        void send(const void *, int);
        void send(const std::string &);
        template <class Iter> void send(Iter &begin, Iter &end);
        void receive(char *, int);
        std::string &receive();
        void shutdown(How h = ShutReadWrite);
        bool operator ==(const TcpConnection &c)
        { return m_clientFd == c.descriptor(); }

        void setDescriptor(int fd) { m_clientFd = fd; }
        int descriptor() const { return m_clientFd; }

    private:
        TcpConnection(const TcpConnection &);
        TcpConnection &operator =(const TcpConnection &);

        int m_clientFd;
    };
}

#endif // TCP_CONNECTION_HXX
