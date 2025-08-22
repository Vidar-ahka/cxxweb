#ifndef ISERVER
#define ISERVER
#include"stdint.h"
class IServer
{
public:
    virtual bool start(uint16_t port) = 0;
    virtual bool stop() = 0;
    virtual ~IServer()= default;
};

#endif