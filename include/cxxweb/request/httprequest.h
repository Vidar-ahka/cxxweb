#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include"string"
#include"irequest.h"
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
    
    HTTPRequest(HTTPRequest & other);
    HTTPRequest(HTTPRequest && other);

    HTTPRequest operator=(HTTPRequest & other);
    HTTPRequest operator=(HTTPRequest && other);
    
    
    ~HTTPRequest() = default;
    void addData(ByteArray data) noexcept;
    void addData(const std::string &  data) noexcept;
    
    std::string getMethod()  const override;
    std::string getPath() const override ;
    std::string getVersion() const override;

    std::string getHeader(std::string key) override ;
    bool hasHeader( std::string key) const override ;
    std::unordered_map<std::string,std::string> GET;
    std::unordered_map<std::string,std::string> POST;
 

private:
    void add_argument();

    mutable std::unique_ptr<ParserHTTPRequest> parser;
    mutable std::unordered_map<std::string,std::string> META;
    
};

}
#endif



