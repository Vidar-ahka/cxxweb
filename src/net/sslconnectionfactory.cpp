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

        try
        {  
            if(server_socket<0)
            {
                throw std::runtime_error("server_socekt < 0");
            }
            if (!ctx) {
                throw std::runtime_error("SSL_CTX is null");
            }
            if (!SSL_CTX_get0_certificate(ctx)) {
                throw std::runtime_error("SSL_CTX has no certificate loaded");
            }
            EVP_PKEY* pkey =  SSL_CTX_get0_privatekey(ctx);
            if (!pkey) {
                throw std::runtime_error("SSL_CTX has no private key loaded");
            }

            if (!SSL_CTX_check_private_key(ctx)) {
                throw std::runtime_error("Private key does not match the certificate");
            }
        }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

}

    
    



