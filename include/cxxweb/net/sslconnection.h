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

        ByteArray  readAll() override;
        ByteArray  read(size_t read_size) override;  
        
        size_t write(ByteArray byte);
        size_t write(const std::string & str)override;
        int   getSocket() const override;  
        bool  is_valid()  const override;
    
    protected:
       bool ssl_valid() const ;
       void check_fun_try(std::string  name_fun);

       SSL * ssl_;
       SSL_CTX *  ctx ;
       int  server_socket;
       int  socket_;
    };
}
#endif