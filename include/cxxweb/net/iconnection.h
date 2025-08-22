#ifndef ICONNECTION_H
#define ICONNECTION_H

#include"stdint.h"
#include"cxxweb/byte/bytearray.h"
namespace CxxWeb
{
    class IConnection
    {
    public:
        virtual  size_t  send(const ByteArray & byte)   = 0;
        virtual  ByteArray read(size_t read_size)   = 0;
        
        virtual  ByteArray readall()   = 0;
        virtual  int  getSocket()   = 0;
        virtual  bool is_valid()  = 0;
        
        virtual ~IConnection() = default;
    protected:
    };
}
#endif