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
    std::string getMethod()  const override
    std::string getPath() const override ;
    std::string getVersion() const override;
    std::string getHeader(std::string key) override ;
    bool hasHeader( std::string key) const override;

private:
    mutable std::unique_ptr<ParserHTTPRequest> parser;
    
};

}
#endif