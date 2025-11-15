#include"cxxweb/request/httprequest.h"

namespace CxxWeb{

    HTTPRequest::HTTPRequest(ByteArray data) noexcept
    {
        
        parser = std::make_unique<ParserHTTPRequest>(data);
       
    }
    HTTPRequest::HTTPRequest(HTTPRequest & other)
    {
       META =  other.META;
        parser = std::make_unique<ParserHTTPRequest>(*other.parser.get());
       GET =  other.GET;
       POST =  other.POST;
    }
    HTTPRequest::HTTPRequest(HTTPRequest && other)
    {
       META  = std::move(other.META);
       parser= std::move(other.parser);
       GET   = std::move(other.GET);
       POST  = std::move(other.POST);  
    }

    HTTPRequest HTTPRequest::operator=(HTTPRequest & other)
    {
       META =  other.META;
       parser = std::make_unique<ParserHTTPRequest>(*other.parser.get());
       GET   =  other.GET;
       POST =  other.POST;
    }   
    HTTPRequest HTTPRequest::operator=(HTTPRequest && other)
    {
          
       META  = std::move(other.META);
       parser= std::move(other.parser);
       GET   = std::move(other.GET);
       POST  = std::move(other.POST);  
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
            return it->second;
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
    void HTTPRequest::add_argument()
    {
        auto  fun = [&](std::unordered_map<std::string,std::string> & map)
        {
            for (auto const& [key, value] : parser->getArgument()) 
            {
                map.emplace(std::string(key), std::string(value));
            }

        };
        if(parser->getMethod()=="GET")
        {
            fun(GET);
        }
        else if(parser->getMethod() == "POST")
        {
            fun(POST);
        }

    }
    


   
   
}