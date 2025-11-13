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
    this->content_type = std::move(content_type);
}
HTTPRespone::HTTPRespone(ByteArray data,std::string content_type,std::string version,
    std::string statusCode, std::string statusMessage) noexcept
{
    new_data = true;
    this->data = data;
    this->content_type = std::move(content_type);
    this->statusCode   = std::move(statusCode);
    this->statusMessage = std::move(statusMessage);
    this->version = std::move(version);
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
 const std::string &   HTTPRespone::getHeaders() noexcept
 {
     if(new_data)
     {      
        head.clear();
        head += version + " " + statusCode + " " + statusMessage + "\r\n" +
        "Content-Type: " + content_type + "\r\n" + 
        "Content-Length: " + std::to_string(data.size()) + "\r\n" +
        "Connection: keep-alive\r\n" +
        "\r\n"; 
        new_data = false;
    }   
    return head;    
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