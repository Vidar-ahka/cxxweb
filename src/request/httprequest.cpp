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
        return std::string(parser->getMethod()); 
    }
    std::string HTTPRequest::getPath() const {
        if(!parser) 
        {
            return "";
        }
        return std::string(parser->getPath());

    }
    
    std::string HTTPRequest::getVersion() const 
    {
        if(!parser)
        {
            return "";
        }    
        return std::string(parser->getVersion());
    }
     std::string HTTPRequest::getHeader(std::string key) 
    {
        if(key.empty())
        {
            return "";
        }
        auto it = META.find(key);
        if(it!=META.end())
        {
            return (*it).second;
        }
        else if(!parser) 
        {
            return  "";
        }   
        std::string result = std::string(parser->get(key));
        if(result.empty())
        {
            return "";
        }
        META[key] = result;
        return result;
    }

    bool HTTPRequest::hasHeader( std::string key) const 
    {
        if(!parser) 
        {
            return  false;
        }
        else if(META.count(key))
        {
            return true;
        }
        std::string result = std::string(parser->get(key));
        if(result.empty())
        {
            return false;
        }
        META[key] = std::move(result);
        return true;
    }


   
   
}