
#ifndef SSLCONNECTIONFACTORY
#define SSLCONNECTIONFACTORY

#include"iconnectionfactory.h"
#include"sslconnection.h"
namespace CxxWeb
{
    class  SSLConnectionFactory: public IConnectionFactory {
    public:
        SSLConnectionFactory(int  & server_socket, SSL_CTX * ctx);

        ~SSLConnectionFactory() = default;  
        std::shared_ptr<IConnection> create() override;
        bool is_valid();
    private:
        bool check();

        SSL_CTX * ctx;
        int server_socket;
    };
}

#endif