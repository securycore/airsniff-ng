#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "locale.h"
#include "TcpServer.hxx"
#include "TcpConnection.hxx"
#include "Ipv4Address.hxx"
#include "Exceptions.hxx"

int file_length(std::ifstream &s)
{
    unsigned long l;
    s.seekg(0, std::ios::end);
    l = s.tellg();
    s.seekg(0, std::ios::beg);
    return l;
}

int main()
{
    setlocale(LC_ALL, "");
    std::string req, fname, answ, line;
    size_t files, filee;
    try {
        komancs::Ipv4Address local(komancs::Any, 3000);
        std::cout << "[I] Starting Komancs Webserver...\n[I] Listening for connections at port 3000...\n\n";
        komancs::TcpServer serv(&local);
        komancs::TcpConnection *c = 0;
        char buffer[1000];
        char *answ_buffer;
        buffer[999] = '\0';
        while (1) {
            c = serv.accept();
            c->receive(buffer, 999);
            std::cout << "Received: " << buffer << std::endl;
            req = buffer;
            files = req.find(" ");
            filee = req.find(" ", files+1);
            fname = req.substr(files+1, filee-4);
            fname = (fname == "/") ? "/index.html" : fname;
            fname.erase(0,1);
            std::cout << files << " " << filee <<  " filename: " << fname << std::endl;
            std::ifstream file(fname.c_str());
            if (!file.is_open()) {
                c->send("HTTP/1.1 \r\n\r\n<html><head><title>Airsniff-ng Webserver</title></head><body><h1>It works</h1>"
                        "<hr><i>Airsniff-ng Webserver</i><br><i>Deltax"
                        "</i></body></html>\r\n\r\n");
                delete c;
                std::cout << fname << " is not found\n";
                continue;
            }
            int len = file_length(file);
            std::ostringstream os;
            os << "HTTP/1.1 200 OK\r\nServer: Komancs\r\nContent-Length: " << len << "\r\n\r\n";
            answ_buffer = new char[len];
            file.read(answ_buffer, len);
            os.write(answ_buffer, len);
            delete[] answ_buffer;
            os << "\r\n\r\n";
            os.seekp(0, std::ios::end);
            len = os.tellp();
            os.seekp(0, std::ios::beg);
            c->send(os.str().c_str(), len);

            delete c;
        }
    } catch (komancs::error::Exception &e) {
        std::cout << e.what() << std::endl;
    }
}
