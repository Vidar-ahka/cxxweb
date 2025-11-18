#ifndef HTTPSSERVER_H
#define HTTPSSERVER_H
#include"memory"
#include"atomic"
#include"cstring"
#include"iostream"
#include"sys/socket.h"
#include"arpa/inet.h"


#include"unistd.h"
#include"sslcontext.h"
#include"iserver.h"
#include"sslconnectionfactory.h"

namespace CxxWeb
{
    
class HttpsServer  : public IServer
{
public:
    HttpsServer()= default;
    HttpsServer(uint16_t port);
    virtual ~HttpsServer();
    void setTimeout(time_t timeout);
    bool accept();
    bool start(uint16_t port) override;
    bool start() override;
    
    int  getSocket() const override;
    bool isValid() const override;
    bool stop() override;
protected:
    bool init_socket();
    int socket_m;
    uint16_t port ;
    sockaddr_in sa_serv;
    bool valid = false;
    
    fd_set readfds; 
    struct timeval timeout;
    time_t  timeout_val{100};
 
};

}

#endif

