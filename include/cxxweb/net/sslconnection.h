#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H 
#include"iconnection.h"
#include"openssl/ssl.h"

#include"sys/socket.h"
#include"arpa/inet.h"
#include <unistd.h>
#include"algorithm"


namespace CxxWeb
{
    class SSLConnection  : public IConnection
    {
    public:
        SSLConnection() ;
        SSLConnection(const int & server_socket , SSL_CTX *  ctx);
        ~SSLConnection();
        
        SSLConnection( const SSLConnection & other) = delete;
        SSLConnection & operator=( const SSLConnection & other) = delete;
        SSLConnection( SSLConnection && other);
        SSLConnection & operator=(SSLConnection && other);
        
        
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
       bool check_fun_try(std::string  name_fun);
       void move_from(SSLConnection&& other);
       

       SSL * ssl_;
       SSL_CTX *  ctx ;
       int  server_socket;
       int  socket_;
       sockaddr_in s_addr;
       socklen_t len;
    };
}
#endif