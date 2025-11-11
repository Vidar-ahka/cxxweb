#ifndef IRESPONE_H
#define IRESPONE_H

#include"cxxweb/data/bytearray.h"
namespace CxxWeb
{

class IRespone
{
public:
    virtual ~IRespone() = default;
    virtual void setData(ByteArray  data) = 0 ;
    virtual ByteArray  getData() = 0 ;
private:
};
}
#endif