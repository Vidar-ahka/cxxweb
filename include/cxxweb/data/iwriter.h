#ifndef IWRITER_H
#define IWRITER_H
#include"bytearray.h"
namespace CxxWeb
{
    class IWriter
    {
    public:
        virtual ~IWriter() = default;
        virtual size_t  write(ByteArray byte);
        virtual size_t  write(const std::string & str);       
    };
}
#endif