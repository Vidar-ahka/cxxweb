
#include"cxxweb/net/httpsserver.h"
namespace CxxWeb
{
    HttpsServer::HttpsServer(std::string  path_cert,  std::string   path_private_key,  std::string  path_ca )
    {
        
    }
    HttpsServer::~HttpsServer()
    {
        stop();
    }  
    bool HttpsServer::start(uint16_t port) 
    {
        this->port = port;
        return true;

    }
    
    bool HttpsServer::stop()
    {   
        close(socket_m);
        return true;
    }


    bool  HttpsServer::init_socket()
    {

        socket_m  = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
        if(socket_m == -1) 
        {
            std::cout<<" socket_m == -1 \n";
            std::cout<<'\n';
            return  false;
        }
        memset(&sa_serv,0,sizeof(sa_serv));
        sa_serv.sin_family = AF_INET;
        sa_serv.sin_addr.s_addr  = INADDR_ANY;
        sa_serv.sin_port = htons(port);
        if(bind(socket_m,(sockaddr*)&sa_serv,sizeof(sa_serv))==-1)
        {
            std::cout<<"!bind \n";
            close(socket_m);
            return false;
        }
        if(listen(socket_m,100)==-1)
        {
            close(socket_m);
            std::cout<<"!listen \n";
            return false;
        }

        return true;



    }
        
}
    


     
