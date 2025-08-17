#ifndef SLLCONTEXT_H
#define SLLCONTEXT_H

#include"string"
#include"openssl/ssl.h"
#include"openssl/err.h"
#include"iostream"
namespace CxxWeb
{
enum class SSLMode 
{
    Server = 0,
    Client,
    TLSv1_2,
    Legacy
};

    class SSLContext
    {
    public:
        SSLContext() = default;
        SSLContext( SSLMode mode ,std::string  path_cert,  std::string   path_private_key,  std::string  path_ca = "");
       
        
        
        bool  init();
        void  set_mode(SSLMode mode );
        void  set_path_cert(const std::string & path_cert);
        void  set_path_private_key(const std::string & path_private_key);
        void  set_path_ca(const std::string& path_ca);
        
        virtual ~SSLContext();
    private:
        const SSL_METHOD* getMethod(SSLMode mode);

        std::string path_cert;
        std::string path_private_key;
        std::string path_ca;
        SSL_CTX    * ctx;    
        SSLMode mode;
    };
}
#endif