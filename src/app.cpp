#include"cxxweb/app.h"

namespace CxxWeb
{
App::App()
{
    server =      std::make_shared<HttpsServer>();
    file_engine = std::make_shared<FileEngine>();
    router =      std::make_shared<Router>(file_engine);
    context =     std::make_shared<SSLContext>();

}

bool App::start()
{
    if(!server->start(port)&&!context->init())
    {
        return false;
    }
    socket = server->getSocket();
    context->init();
    con_factory= std::make_shared<SSLConnectionFactory> (socket,context->getCTX());
    
    if(!con_factory->is_valid())
    {
        return false;
    }
    return true;
}



void App::setPort(uint16_t port)
{
    this->port = port;
}
void App::setPathCert (std::string  path_cert)
{
    context->set_path_cert(path_cert);

}
void App::setPathPrivateKey (std::string   path_private_key)
{
    context->set_path_private_key(path_private_key); 
}
void App::setPathTemplates(std::string path_templates)
{
    file_engine->setPathTemplate(path_templates);
}
void App::setPathStaticFile(std::string path_static_file)
{
    file_engine->setPathStatic(path_static_file); 
}
void App::addHandler(std::string url , std::function<std::shared_ptr<HTTPRespone>(HTTPRequest&)> handler)
{
    router->addHandler(url,handler);
}
void App::setTimeout(time_t  timeout)
{
    server->setTimeout(timeout);
}



}

    