#include"cxxweb/respone/httprespone.h"
namespace CxxWeb
{
HTTPRespone::HTTPRespone() noexcept : content_type("text/html"),statusMessage("OK") , statusCode("200"), version("HTTP/1.1") 
{
    new_data = true;
}
    
HTTPRespone::HTTPRespone(ByteArray data) noexcept: HTTPRespone() 
{
    this->data = data;

}
HTTPRespone::HTTPRespone(ByteArray data,std::string content_type) noexcept : HTTPRespone()
{
    this->data = data;
    this->content_type = content_type;
}
HTTPRespone::HTTPRespone(ByteArray data,std::string content_type,std::string version,
    std::string statusCode, std::string statusMessage) noexcept
{
    new_data = true;
    this->data = data;
    this->content_type = content_type;
    this->statusCode   = statusCode;
    this->statusMessage = statusMessage;
    this->version = version;
}
void HTTPRespone::setData(ByteArray  data) noexcept 
{
    this->data = data;
    new_data = true;
}

ByteArray  HTTPRespone::getData() noexcept 
{
    return data;
}

void HTTPRespone::setVersion(std::string version) noexcept
{
    new_data = true;
    this->version = version;;
}
    
void HTTPRespone::setStatusMessage(std::string status)  noexcept
{
    new_data = true;
    this->statusMessage = status;
}
void HTTPRespone::setStatusCode(std::string code)  noexcept
{
    new_data = true;
    this->statusCode = code;
}
void HTTPRespone::setContentType(std::string content_type)  noexcept
{
    new_data = true;
    this->content_type = content_type;
}   
}