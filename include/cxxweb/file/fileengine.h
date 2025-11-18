#ifndef FILEENGINE_H
#define FILEENGINE_H

#include"unordered_map"
#include"memory"
#include"cxxweb/data/bytearray.h"
#include"cxxweb/template/htmltemplatekey.h"
#include"cxxweb/file/staticfilereader.h"

namespace CxxWeb
{


class FileEngine
{
public:
    FileEngine()=default;

    FileEngine( const std::string & path_template ,const  std::string & path_static);

    ~FileEngine() = default;        
    void setPathTemplate(const std::string & path_template);
    void setPathStatic(const std::string   & path_static  );

    
    ByteArray getTemplate(const std::string & path);
    ByteArray getTemplate(const std::string & path,std::unordered_map<std::string , std::string> & keys);
    ByteArray getStatic(const std::string & path);
    
private:
    ByteArray readFile(std::string path);


    std::string path_static;
    std::string path_template;
    std::unordered_map<std::string , ByteArray > static_map;
    std::unordered_map<std::string , ByteArray > template_map;
    std::unordered_map<std::string , std::shared_ptr<HTMLTemplateKey>> template_key_map;    
};
}
#endif