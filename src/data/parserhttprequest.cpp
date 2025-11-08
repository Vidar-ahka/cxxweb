

#include"cxxweb/data/parserhttprequest.h"
namespace CxxWeb
{



ParserHTTPRequest::ParserHTTPRequest(ByteArray data)
{
    this->data = data;
    parse_main_data();
}
void    ParserHTTPRequest::parse(const std::string& data) 
{
    this->data.write(data.c_str());
    parse_main_data();
}
void    ParserHTTPRequest::parse(ByteArray data) 
{
    this->data = data;
    parse_main_data();
}

std::string    ParserHTTPRequest::getMethod()
{
    return method;
}
std::string    ParserHTTPRequest::getVersion()
{
    return version;
}
std::vector<std::pair<std::string_view,std::string_view>> & ParserHTTPRequest::getArgument()
{
    return this->argument;
}
  
std::string_view ParserHTTPRequest::get(const std::string & key,std::string separator ) 
{
    std::string_view str(data.data(),data.size());
    size_t find_pos = str.find(key);
    if(str.find(key) == std::string_view::npos)
    {
        return std::string_view();
    }   
    find_pos+=key.size();
    find_pos = str.find(separator,find_pos);
    if(find_pos==std::string_view::npos)
    {
        return std::string_view();
    }
    find_pos+=separator.size();
    size_t new_line =  str.find("\n",find_pos);
    if(new_line == std::string::npos)
    {
        return std::string_view();
    }
    std::string_view result(str.data()+find_pos+1,new_line-find_pos-1);
    return result;
}  
    

void ParserHTTPRequest::parse_main_data()
{

   



}

}
