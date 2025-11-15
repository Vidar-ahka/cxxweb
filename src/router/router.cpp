#include "cxxweb/router/router.h"

namespace CxxWeb {

Router::Router(std::shared_ptr<FileEngine> file_engine)
{
    this->file_engine = file_engine;
}

void Router::addHandler(const std::string& path, Handler   handler)
{
    handler_map[path] = handler;
}

std::shared_ptr<HTTPRespone> Router::get(HTTPRequest& request)
{
    std::string path = request.getPath();   
    auto it  = handler_map.find(path);
    std::shared_ptr<HTTPRespone> respone;
    if(it != handler_map.end())
    {   
        respone =  it->second(request);
    }
    else 
    {
        ByteArray data = file_engine->getStatic(path); 
        if(data.empty())
        {
            return std::make_shared<HTTPRespone>();
        }
        respone  = std::make_shared<HTTPRespone>(data); 
        respone->setContentType(FileConntentTypeRegister::instanse().get(path));
        respone->setVersion(request.getVersion());
        respone->setStatusCode("200");
        respone->setStatusMessage("OK");
    }
    return respone;
}

} 
