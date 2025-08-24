#ifndef IREADER_H
#define IREADER_H
#include"bytearray.h"
namespace CxxWeb
{    
    class IReader
    {
    public:
        virtual ~IReader() = default;  
        virtual  ByteArray  readAll() = 0 ;
        virtual  ByteArray  read(size_t read_size)= 0;
    };   
}
#endif