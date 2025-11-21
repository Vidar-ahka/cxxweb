#ifndef FILECONNTENTTYPEREGISTER_H
#define FILECONNTENTTYPEREGISTER_H
#include"unordered_map"
#include"string"
namespace CxxWeb
{

class FileConntentTypeRegister
{
    
public:

   static FileConntentTypeRegister & instanse()
   {
    static FileConntentTypeRegister  var;
    return var;
   }
   std::string get(const std::string & path) const ;

   FileConntentTypeRegister(const FileConntentTypeRegister &) = delete;
   FileConntentTypeRegister(FileConntentTypeRegister &&) = delete;
   FileConntentTypeRegister& operator=(const FileConntentTypeRegister &) = delete;
   FileConntentTypeRegister& operator = (FileConntentTypeRegister &&) = delete;
    
private:
    FileConntentTypeRegister();
    std::unordered_map<std::string,std::string> types;
    size_t max_size_exeption{0};
};
}
#endif
