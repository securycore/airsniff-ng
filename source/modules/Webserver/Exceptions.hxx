#ifndef KOMANCS_EXCEPTION_HXX
#define KOMANCS_EXCEPTION_HXX

#include <cstdio>
#include <string>
#include <cstring>

#include <errno.h>

namespace komancs {
    namespace error {
    class Exception
    {
    public:
        Exception(const char *msg = NULL) :m_message(msg) {}
        Exception(const std::string &msg) :m_message(msg) {}
        ~Exception() {}

        virtual void setMessage(const std::string &msg) { m_message = msg; }
        virtual void setMessage(const char *msg) { m_message = msg; }
        virtual const char *what() const { return m_message.c_str(); }

    private:
        std::string m_message;
    };

    class InvalidPortNumber : public Exception
    {
    public:
        InvalidPortNumber(int port)
            : Exception("The range of the port is invalid!"), m_port(port)
        {}

        int port() const { return m_port; }

    private:
        int m_port;
    };

    class SystemException : public Exception
    {
    public:
        SystemException(const char *sysfunc = "unknow")
            : Exception(std::string(sysfunc) + std::string(": ") + std::string(strerror(errno)))
        {}
    };
    }
}

#endif // KOMANCS_EXCEPTION_HXX
