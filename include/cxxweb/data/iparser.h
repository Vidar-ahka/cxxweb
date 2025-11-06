#ifndef IPARSER_H
#define IPARSER_H
#include"string"
#include"bytearray.h"
namespace CxxWeb
{
    class IParser
    {
    public:
        virtual ~IParser() = default;
        virtual void    parse(const std::string& data) = 0;
        virtual void    parse(ByteArray data)          = 0 ;
        virtual std::string_view get(const std::string & key,std::string separator = ":");
    };   
}
#endif
