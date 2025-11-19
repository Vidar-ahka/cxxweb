#ifndef CXXWEB_APP_H
#define CXXWEB_APP_H
#include"memory"
#include"unordered_map"
#include"future"
#include"functional"
#include"cxxweb/net/httpsserver.h"
#include"cxxweb/file/fileengine.h"
#include"cxxweb/router/router.h"
#include"cxxweb/net/sslcontext.h"
#include"cxxweb/respone/httprespone.h"
#include"cxxweb/request/httprequest.h"
#include"cxxweb/net/sslconnectionfactory.h"

namespace CxxWeb
{

class App
{
public:
    App();
    ~App() = default;
    void setPort(uint16_t port);
    void setPathCert (std::string  path_cert);
    void setPathPrivateKey (std::string   path_private_key);
    void setPathTemplates(std::string path_templates);
    void setPathStaticFile(std::string path_static_file);
    void addHandler(std::string url , std::function<std::shared_ptr<HTTPRespone>(HTTPRequest&)> handler);
    void setTimeout(time_t  timeout);
    
private:
    std::shared_ptr<HttpsServer> server;
    std::shared_ptr<FileEngine> file_engine;
    std::shared_ptr<Router>  router;
    std::shared_ptr<SSLContext> context;
    std::shared_ptr<SSLConnectionFactory> con_factory;
    uint16_t port ;



    
    
};

}
#endif