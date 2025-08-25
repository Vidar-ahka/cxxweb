#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H 
#include"iconnection.h"
#include"openssl/ssl.h"

#include"sys/socket.h"
#include"arpa/inet.h"
#include <unistd.h>



namespace CxxWeb
{
    class SSLConnection  : public IConnection
    {
    public:
        SSLConnection() ;
        SSLConnection(const int & server_socket , SSL_CTX *  ctx);
        ~SSLConnection();
        bool start(const int & server_socket , SSL_CTX *  ctx);
        bool start();
        bool stop();
    protected:
       SSL * ssl_;
       SSL_CTX *  ctx ;

       int  server_socket;
       int  socket_;
    };
}
#endif