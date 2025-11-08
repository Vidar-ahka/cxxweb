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
   
}