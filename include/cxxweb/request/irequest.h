#ifndef IHTTPREQUEST_H
#define IHTTPREQUEST_H
#include"string"

namespace CxxWeb
{
class IRequest {
public:
    virtual ~IRequest() = default;
    virtual std::string getMethod() const = 0;
    virtual std::string getPath() const = 0;
    virtual std::string getHeader(std::string key) = 0;
    virtual std::string getVersion() const  = 0;
    virtual bool hasHeader(      std::string key) const = 0;
};

}


#endif