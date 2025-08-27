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
        size_t  write(ByteArray byte) override
        {
           int count =   SSL_write(ssl_,byte.data(),byte.size());
           return count ;
        }
        size_t  write(const std::string & str) override
        {
           int count =   SSL_write(ssl_,str.data(),str.size());
           return count;
        }
        int  getSocket() const  override
        {
            return socket_;
        }
        bool is_valid()  const  override
        {
            return true;
        }
    
    protected:
       SSL * ssl_;
       SSL_CTX *  ctx ;
       int  server_socket;
       int  socket_;
    };
}
#endif