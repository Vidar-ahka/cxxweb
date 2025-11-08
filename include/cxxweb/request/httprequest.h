#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include"string"
#include"cxxweb/request/irequest.h"
#include"cxxweb/data/bytearray.h"
#include"unordered_map"
#include"memory"
#include"cxxweb/data/parserhttprequest.h"

namespace CxxWeb
{

    
class HTTPRequest  : public IRequest{
public:
    HTTPRequest() = default;
    HTTPRequest(ByteArray data) noexcept;
    void addData(ByteArray data) noexcept;
    void addData(const std::string &  data) noexcept;
    
    ~HTTPRequest() = default;
    std::string getMethod()  const override{return "";};
    std::string getPath() const override {return "";};
    std::string getHeader(std::string key) override {return "";};
    bool hasHeader( std::string key) const override {return false;};

private:

    mutable std::unique_ptr<ParserHTTPRequest> parser;
    
};

}
#endif