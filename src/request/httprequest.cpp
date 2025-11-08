#include"cxxweb/request/httprequest.h"

namespace CxxWeb{

    HTTPRequest::HTTPRequest(ByteArray data) noexcept
    {
        
        parser = std::make_unique<ParserHTTPRequest>(data);
       
    }
     void HTTPRequest ::addData(ByteArray data) noexcept
    {
        if(!parser)
        {
            parser = std::make_unique<ParserHTTPRequest>();
        }
        parser->parse(data);
    }
     void HTTPRequest ::addData( const std::string  &  data) noexcept
    {
        if(!parser)
        {
            parser = std::make_unique<ParserHTTPRequest>();
        }
        parser->parse(data);
    }
     
    std::string HTTPRequest::getMethod()  const 
    {
        if(!parser) 
        {
            return "";
        }
        return parser->getMethod(); 
    }
    std::string HTTPRequest::getPath() const {
        if(!parser) 
        {
            return "";
        }
        return parser->getPath();

    }
    std::string HTTPRequest::getVersion() const 
    {
        if(!parser)
        {
            return "";
        }    
        return parser->getVersion();
    }
    std::string HTTPRequest::getHeader(std::string key) {
        return "";
    } 
    bool HTTPRequest::hasHeader( std::string key) const {
        return false;
    }
   
}