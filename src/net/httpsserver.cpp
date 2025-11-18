
#include"cxxweb/net/httpsserver.h"
namespace CxxWeb
{
    HttpsServer::HttpsServer(uint16_t port)
    {
        this->port = port;
    }
    HttpsServer::~HttpsServer()
    {
        stop();
    }  
    bool HttpsServer::start()
    {
        if(!init_socket())
        {
            return  false;
        }
        FD_ZERO(&readfds);
        FD_SET(socket_m, &readfds);
        return true;
    } 
    void HttpsServer::setTimeout(time_t  timeout)
    {
        timeout_val = timeout;
    }
    bool HttpsServer::accept()
    {
        timeout.tv_sec  = timeout_val;
        timeout.tv_usec = 0;
        return select(socket_m+1,&readfds,nullptr,nullptr,&timeout)>0;
    }
    bool HttpsServer::start(uint16_t port) 
    {
        this->port = port;
        return start();
    }
    bool HttpsServer::stop()
    {   
        close(socket_m);
        return true;
    }
    int  HttpsServer::getSocket() const 
    {
        return socket_m;
    }
 
    bool  HttpsServer::isValid() const 
    {
        return valid&& socket_m>0;
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
        valid = true;
        return true;



    }
        
}
    


     
