#include"cxxweb/net/sslconnectionfactory.h"


namespace CxxWeb
{
    SSLConnectionFactory::SSLConnectionFactory(int  & server_socket, SSL_CTX * ctx) : server_socket(server_socket) , 
    ctx(ctx)
    {       
    }    
    std::shared_ptr<IConnection> SSLConnectionFactory::create() 
    {
      
        return std::make_shared<SSLConnection>(server_socket,ctx);
    }
    bool SSLConnectionFactory::is_valid()
    {
        return check();
    }
    bool SSLConnectionFactory::check() {  
            if(server_socket<0)
            {
                std::cout <<"server_socekt < 0";
                return false;
            }
            if (!ctx) {
                std::cout <<"SSL_CTX is null";
                return false;
            }
            if (!SSL_CTX_get0_certificate(ctx)) {
                std::cout<<"SSL_CTX has no certificate loaded";
                return false;
            }
            EVP_PKEY* pkey =  SSL_CTX_get0_privatekey(ctx);
            if (!pkey) {
                std::cout <<"SSL_CTX has no private key loaded";
                return false;
            }

            if (!SSL_CTX_check_private_key(ctx)) {
                std::cout <<"Private key does not match the certificate";
                return false;
            }
        return true;
}

}

    
    



