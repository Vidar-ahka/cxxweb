#ifndef IWRITER_H
#define IWRITER_H
#include"bytearray.h"
#include"string"
namespace CxxWeb
{
    class IWriter
    {
    public:
        virtual ~IWriter() = default;
        virtual size_t  write(ByteArray byte) = 0 ;
        virtual size_t  write(const std::string & str) = 0;       
    };
}
#endif