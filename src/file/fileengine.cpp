#include"cxxweb/file/fileengine.h"

namespace CxxWeb
{



FileEngine::FileEngine( const std::string & path_template ,const  std::string & path_static)
{
    setPathTemplate(path_template);
    setPathStatic(path_static);
    
}

void FileEngine::setPathTemplate(const std::string & path_template)
{
    this->path_template = path_template;
    if(this->path_template.back()=='/')
    {
        this->path_template.pop_back();
    }
}
void FileEngine::setPathStatic(const std::string   & path_static  )
{
    this->path_static = path_static;
    if(this->path_static.back()=='/')
    {
        this->path_static.pop_back();
    }
    
}

ByteArray FileEngine::getTemplate(const std::string & path)
{
    try
    {
        auto it = template_map.find(path);
        if(it == template_map.end())
        {
            ByteArray data = readFile(path_template+path);
            template_map[path]  = data;
            return data;
        }
        return (*it).second;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ByteArray();
    }
}
ByteArray FileEngine::getTemlate(const std::string & path,std::unordered_map<std::string , std::string> & keys)
{

    try
    { 
        auto it = template_key_map.find(path);
        std::shared_ptr<HTMLTemplateKey> tmp;
        if(it == template_key_map.end())
        {
            ByteArray data = readFile(path_template+path);
            tmp = std::make_shared<HTMLTemplateKey>(data);
            template_key_map[path] =  tmp;
        }
        else 
        {   
            tmp =  (*it).second;
        }
        return tmp->get(keys);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ByteArray();
    }
}
ByteArray FileEngine::getStatic(const std::string & path)
{
    try
    {
        auto it = static_map.find(path);
        if(it == static_map.end())
        {
            ByteArray data = readFile(path_static+path);
            static_map[path]  = data;
            return data;
        }
        return (*it).second;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ByteArray();
    }
}

    

ByteArray FileEngine::readFile(std::string path)
{
    StaticFileReader file(path);
    if(!file.open())
    {
        throw "file: "  +path+" dont opne\n";
    }
    ByteArray data = file.readAll();
    if(data.empty())
    {   
        throw "file: "  +path+" empty\n";
        
    }
    return data;
}
}