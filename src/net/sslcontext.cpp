#include"cxxweb/net/sslcontext.h"
namespace CxxWeb
{


    SSLContext::SSLContext(SSLMode mode ,std::string  path_cert, std::string path_private_key,std::string  path_ca) : 
    mode(mode),
    path_cert(path_cert), 
    path_private_key(path_private_key),
    path_ca(path_ca)
    {

    }
    
  


    SSLContext :: ~SSLContext()
    {
          SSL_CTX_free(ctx);
    }
    bool  SSLContext::init(){

        SSL_library_init();                 
        SSL_load_error_strings(); 
          
        ctx = SSL_CTX_new(const_cast<SSL_METHOD*>(getMethod(mode)));
       
        if(SSL_CTX_use_certificate_file(ctx, this->path_cert.c_str(),SSL_FILETYPE_PEM)<=0)
        {
           std::cout<<"\n"<<"not cert " << path_cert <<'\n';
           ERR_print_errors_fp(stderr);
           SSL_CTX_free(ctx);
           return false;
        }
        if(!SSL_CTX_use_PrivateKey_file(ctx,path_private_key.c_str(),SSL_FILETYPE_PEM))
        {
            std::cout<<"\n! not privete key \n" ;
            ERR_print_errors_fp(stderr);        
            return false;
        }
        if(!SSL_CTX_load_verify_locations(ctx, this->path_ca.c_str(),NULL))
        {
            std::cout<< "\n !  load verify location \n"  ;
        }
        return true;
    }

    void  SSLContext::set_mode( SSLMode mode)
    {
        this->mode = mode;
    }
    void  SSLContext::set_path_cert(const std::string & path_cert)
    {
        this->path_cert = path_cert;
    }
    void  SSLContext::set_path_private_key(const std::string &path_private_key)
    {
        this->path_private_key = path_private_key;
    }
    void  SSLContext::set_path_ca(const std::string & path_ca)
    {
        this->path_ca = path_ca;
    }

}