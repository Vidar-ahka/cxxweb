#ifndef ROUTER_H
#define ROUTER_H
#include"functional"
#include"cxxweb/respone/httprespone.h"
#include"cxxweb/request/httprequest.h"
#include"cxxweb/file/fileengine.h"
#include"cxxweb/file/fileconntenttyperegister.h"
#include"memory"
#include"unordered_map"


namespace CxxWeb {

using Handler = std::function<std::shared_ptr<HTTPRespone>(HTTPRequest&)>;

class Router
{
public:
    Router(std::shared_ptr<FileEngine> file_engine);

    void addHandler(const std::string& path, Handler handler);

    std::shared_ptr<HTTPRespone> get(HTTPRequest& request);

private:
    std::shared_ptr<FileEngine> file_engine; 
    std::unordered_map<std::string, Handler> handler_map;
};

}

#endif