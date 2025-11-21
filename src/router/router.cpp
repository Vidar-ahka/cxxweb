#include "cxxweb/router/router.h"

namespace CxxWeb {

Router::Router(std::shared_ptr<HTTPResponeRender> respone_render)
{
    this->respone_render = respone_render;
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
        respone =  respone_render->renderStatic(request,path);
    }
    return respone;
}

} 
