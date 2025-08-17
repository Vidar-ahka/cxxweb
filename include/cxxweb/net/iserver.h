#ifndef ISERVER
#define ISERVER
#include"stdint.h"
class IServer
{
public:
    virtual bool start(uint16_t port) = 0;
    virtual bool stop();
    virtual ~IServer()= default;
};

#endif