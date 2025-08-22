#ifndef HTTPSSERVER_H
#define HTTPSSERVER_H
#include"memory"
#include"atomic"
#include"cstring"
#include"iostream"
#include"sys/socket.h"
#include"arpa/inet.h"

#include"sslconnection.h"
#include"unistd.h"
#include"sslcontext.h"
#include"iserver.h"

namespace CxxWeb
{
    
class HttpsServer  : public IServer
{
public:
    
    HttpsServer(std::string  path_cert,  std::string   path_private_key,  std::string  path_ca = "");

    virtual ~HttpsServer();
    bool start(uint16_t port) override;
    bool stop() override;
    
protected:
    bool init_socket();

    int socket_m;
    uint16_t port ;
    sockaddr_in sa_serv;

    std::unique_ptr<SSLContext> ssl;
    bool work;
 
};

}

#endif

