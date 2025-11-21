#ifndef CXXWEB_HTTPRESPONERENDER_H
#define CXXWEB_HTTPRESPONERENDER_H
#include"memory"
#include"httprespone.h"
#include"cxxweb/file/fileengine.h"
#include"cxxweb/request/httprequest.h"
#include"cxxweb/file/fileconntenttyperegister.h"
namespace CxxWeb
{
class HTTPResponeRender
{
public:
    HTTPResponeRender(std::shared_ptr<FileEngine> file_engine);
    std::shared_ptr<HTTPRespone> renderStatic  (HTTPRequest & request, const std::string & path_static);
    std::shared_ptr<HTTPRespone> renderTemplate(HTTPRequest & request, const std::string & path_template_file);
    std::shared_ptr<HTTPRespone> renderTemplate(HTTPRequest & request, const std::string & path_template_file, std::unordered_map<std::string , std::string > & context);
private:
   void  buildRespone(std::shared_ptr<HTTPRespone> & respone,HTTPRequest & requse,  const std::string & path);
   std::shared_ptr<FileEngine>  file_engine;
    
};
}

#endif

