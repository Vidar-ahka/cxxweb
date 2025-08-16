#include"cxxweb/net/sslcontext.h"
namespace CxxWeb
{


    SSlContext::SSlContext(SSL_METHOD * method,std::string  path_cert, std::string path_private_key,std::string  path_ca) : 
    method(method),
    path_cert(path_cert), 
    path_private_key(path_private_key),
    path_ca(path_ca){}
    
    SSlContext :: ~SSlContext()
    {
          SSL_CTX_free(ctx);
    }
    bool  SSlContext::init(){

        SSL_library_init();                 
        SSL_load_error_strings(); 
          
        ctx = SSL_CTX_new(const_cast<SSL_METHOD*>(method));
       
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

}