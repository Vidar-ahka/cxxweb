#include"cxxweb/respone/httpresponerender.h"
namespace CxxWeb
{


HTTPResponeRender::HTTPResponeRender(std::shared_ptr<FileEngine> file_engine)
{
    this->file_engine  = file_engine;
}
    
std::shared_ptr<HTTPRespone> HTTPResponeRender::renderStatic (HTTPRequest & request, const std::string & path_static_file)
{
    
    ByteArray data = file_engine->getStatic(path_static_file); 
    std::shared_ptr<HTTPRespone> respone  = std::make_shared<HTTPRespone>(data);
    buildRespone(respone,request,path_static_file);
    return respone;

}
std::shared_ptr<HTTPRespone> HTTPResponeRender::renderTemplate(HTTPRequest & request, const std::string   & path_template_file)
{

    ByteArray data  =  file_engine->getTemplate(path_template_file);
    std::shared_ptr<HTTPRespone> respone = std::make_shared<HTTPRespone>(data);
    buildRespone(respone,request,path_template_file);  
    return respone;  
}
std::shared_ptr<HTTPRespone> HTTPResponeRender::renderTemplate(HTTPRequest & request, const std::string &path_template_file, std::unordered_map<std::string , std::string > & keys)
{    
    ByteArray data  =  file_engine->getTemplate(path_template_file,keys);
    std::shared_ptr<HTTPRespone> respone = std::make_shared<HTTPRespone>(data);
    buildRespone(respone,request,path_template_file); 
    return respone;  
}

void HTTPResponeRender::buildRespone(std::shared_ptr<HTTPRespone> & respone,HTTPRequest & request,  const std::string & path)
{
    respone->setContentType(FileConntentTypeRegister::instanse().get(path));
    respone->setVersion(request.getVersion());
    respone->setStatusCode("200");
    respone->setStatusMessage("OK");      
}

}
