#ifndef ISERVER
#define ISERVER
#include"stdint.h"
class IServer
{
public:
    virtual ~IServer()= default;
    virtual bool start() = 0;
    virtual bool start(uint16_t port) = 0;
    virtual bool stop() = 0;    
    virtual int  getSocket() const = 0;
    virtual bool isValid() const =0;
};

#endif