#ifndef SLLCONTEXT_H
#define SLLCONTEXT_H

#include"string"
#include"openssl/ssl.h"
#include"openssl/err.h"
#include"iostream"
namespace CxxWeb
{

    class SSlContext
    {
    public:
        SSlContext(  SSL_METHOD * method , std::string path_cert, std::string path_private_key,std::string path_ca = "");
        
        bool  init();
        virtual ~SSlContext();
    private:
        std::string path_cert;
        std::string path_private_key;
        std::string path_ca;
        SSL_CTX    * ctx;
        SSL_METHOD * method;
        
    };
}
#endif