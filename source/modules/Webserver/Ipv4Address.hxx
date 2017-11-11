#ifndef IPV4_ADDRESS_HXX 
#define IPV4_ADDRESS_HXX 

#include "InetGlobals.hxx"

namespace komancs {
    enum HostType {
          Any = INADDR_ANY
        , None = INADDR_NONE
        , LoopBack = INADDR_LOOPBACK
        , BroadCast = INADDR_BROADCAST };

    class Ipv4Address
    {
    public:
        Ipv4Address(const Ipv4Address &);
        Ipv4Address(const struct ::sockaddr_in &);
        Ipv4Address(const char *ip, int port);
        Ipv4Address(HostType type, int port);
        void setPort(int);
        void setAddress(const char *);
        void setAddress(const struct ::sockaddr_in &);
        void setHostType(HostType);
        const struct ::sockaddr_in &address() const { return m_address; }
        struct ::sockaddr_in *addressPointer() { return &m_address; }
        size_t size() const { return sizeof(m_address); }
        Ipv4Address &operator =(const Ipv4Address &);
        bool operator ==(const Ipv4Address &);

    private:
        void init();
        struct ::sockaddr_in m_address;
    };
}

#endif // IPV4_ADDRESS_HXX 
