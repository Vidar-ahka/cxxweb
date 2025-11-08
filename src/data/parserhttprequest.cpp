

#include"cxxweb/data/parserhttprequest.h"
namespace CxxWeb
{



ParserHTTPRequest::ParserHTTPRequest(ByteArray data)
{
    this->data = data;
    parse_main_data();
}
ParserHTTPRequest::ParserHTTPRequest(ParserHTTPRequest & other)
{
    data = other.data;
    path = other.path;
    method = other.method;
    argument = other.argument;

}
ParserHTTPRequest::ParserHTTPRequest(ParserHTTPRequest && other)
{
   
    data = std::move(other.data);
    path = std::move(other.path);
    method = std::move(other.method);
    argument = std::move(other.argument);
}
ParserHTTPRequest &  ParserHTTPRequest::operator=(ParserHTTPRequest & other)
{
    if(this ==  &other)
    {
        return *this;
    }
    data = other.data;
    path = other.path;
    method = other.method;
    argument = other.argument;
    return *this;
}
ParserHTTPRequest &  ParserHTTPRequest::operator=(ParserHTTPRequest && other)
{
    if(this ==  &other)
    {
        return *this;
    }
    data = std::move(other.data);
    path = std::move(other.path);
    method = std::move(other.method);
    argument = std::move(other.argument);
    return *this;
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

    std::string_view str(data.data(),data.size());
    size_t i =0;
    auto skip_space = [&](){while(i<str.size() && str[i]==' ')++i;};
    auto  read_str = [&](std::string & result, std::function<bool(char)>  fun)
    {while(i<str.size()&& !fun(str[i]))   result.push_back(str[i++]);};
    skip_space();
    read_str(method,[](char c)->bool
    {return  c == ' ' ;});

    skip_space();
    read_str(path,[](char c)->bool 
    { return c=='?' ||c==' ' ;});
     
   
    if(i<str.size()&&str[i]=='?')
    {
        size_t beg = ++i;
        size_t eq = i;
        while(i<str.size() && str[i]!=' ')
        {
            if(str[i]=='=')
            {
                eq = i;
            }
            else if(str[i]=='&')
            {
                if(eq!= std::string_view::npos)
                {
                    this->argument .push_back(
                    {std::string_view(str.data()+beg,eq-beg), 
                    std::string_view(str.data()+eq+1 ,i-eq-1)});
                }
                beg = i+1;
                eq = std::string::npos;
            }
            ++i;
        }
        if(eq != std::string::npos)
        {
            this->argument .push_back({std::string_view(str.data()+beg,eq-beg), 
            std::string_view(str.data()+eq+1 ,i-eq-1)});           
        }
    }  
    skip_space();
    
    read_str(version,[](char c)->bool
    { return std::isspace(c);});
     



}

}
