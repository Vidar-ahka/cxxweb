#ifndef HTTPRESPONE
#define HTTPRESPONE
#include"irespone.h"
#include"string"
namespace CxxWeb
{

class HTTPRespone : public IRespone
{
public:
    HTTPRespone() noexcept;

    HTTPRespone(ByteArray data) noexcept;
    HTTPRespone(ByteArray data,std::string content_type) noexcept;
    HTTPRespone(ByteArray data,std::string content_type,std::string version,std::string statusCode, 
    std::string statusMessage) noexcept;
    ~HTTPRespone() = default;
    
    
    void setData(ByteArray  data) noexcept override;
    
    
    ByteArray  getData() noexcept override;
    const std::string &   getHeaders() noexcept;
    
    void setVersion(std::string version) noexcept;

    void setStatusMessage(std::string status) noexcept;
    void setStatusCode (std::string code)   noexcept ;
    void setContentType(std::string content_type) noexcept;
    
    
    
private:
    
    ByteArray data;
    std::string  head;
    std::string statusCode;
    std::string statusMessage;
    std::string  version;
    std::string  content_type;
    bool new_data = false;
};
}
#endif