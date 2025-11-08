#ifndef PARSERHTTPREQUEST_H
#define PARSERHTTPREQUEST_H
#include"cxxweb/data/bytearray.h"
#include"cxxweb/data/iparser.h"
#include"vector"
#include"functional"
namespace CxxWeb
{
class ParserHTTPRequest : public IParser
{
public:
    ParserHTTPRequest() =default;
    ~ParserHTTPRequest() = default;
    
    
    ParserHTTPRequest(ByteArray data);
    ParserHTTPRequest(ParserHTTPRequest & other);
    ParserHTTPRequest(ParserHTTPRequest && other);
    ParserHTTPRequest &  operator=(ParserHTTPRequest & other);
    ParserHTTPRequest &  operator=(ParserHTTPRequest && other);
    
    
    void    parse(const std::string& data) override ;
    void    parse(ByteArray data) override;
    std::string    getMethod()  const;
    std::string    getVersion() const ;
    std::vector<std::pair<std::string_view,std::string_view>>   & getArgument()  ;
    

    std::string_view get(const std::string & key,std::string separator = ":") override;
private:
    void parse_main_data();
    

    std::string method;
    std::string version;
    std::string path;
    std::vector<std::pair<std::string_view,std::string_view>> argument;
    
    ByteArray data;
};
    

}
#endif