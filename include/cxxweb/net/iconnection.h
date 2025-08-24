#ifndef ICONNECTION_H
#define ICONNECTION_H

#include"stdint.h"
#include"cxxweb/data/bytearray.h"
#include"cxxweb/data/ireader.h"
#include"cxxweb/data/iwriter.h"

namespace CxxWeb
{
    class IConnection : public  IWriter , public IReader
    {
    public:
        virtual ~IConnection() = default;
        virtual  bool start() = 0;
        virtual  bool stop()  = 0;
        virtual  int  getSocket() const  = 0;
        virtual  bool is_valid()  const  = 0;
    
    };
}
#endif 