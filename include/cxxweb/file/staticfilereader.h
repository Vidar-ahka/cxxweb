#ifndef STATICFILEREADER_H
#define STATICFILEREADER_H
#include"ifilereader.h"
#include"fstream"
namespace CxxWeb
{
    class StaticFileReader : public IFileReader
    {
    public:
        
        StaticFileReader() = default;
    
        StaticFileReader(std::string & file_path);
        ~StaticFileReader();

        bool open()override;
        bool open(const std::string  & file_path) override;
        bool close() override;
        ByteArray read(size_t size) override{return ByteArray();}
        ByteArray readAll() override {return ByteArray();}
        
        
        bool is_open() const override;
        bool empty() const override;
        
        size_t size() const override;                 
        std::string  path() const override;
    private:
        std::string file_path;
        std::ifstream stream;
        size_t size_ {0}; 
    };

}

#endif