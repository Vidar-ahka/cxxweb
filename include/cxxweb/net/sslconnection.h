#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H 
#include"iconnection.h"
#include"openssl/ssl.h"
#include"sys/socket.h"
#include"arpa/inet.h"
#include <unistd.h>   

namespace CxxWeb
{
    class SSLConnection : public IConnection
    {
    public:
        SSLConnection() = default;
        SSLConnection(const int & server_socket ,  SSL_CTX  *  ctx);
        ~SSLConnection();
        
        size_t  send(const ByteArray & byte)  override;
        ByteArray readall()  override;
        ByteArray read(size_t read_size) override;
        
        int  getSocket()  override;
        bool is_valid() override;
    private:
       SSL* ssl_;
       int  socket_;
       bool valid;
    };
}
#endif