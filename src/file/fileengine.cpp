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