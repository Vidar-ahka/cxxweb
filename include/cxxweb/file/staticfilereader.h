#ifndef STATICFILEREADER_H
#define STATICFILEREADER_H
#include"ifilereader.h"
#include"fstream"
#include"memory"
namespace CxxWeb
{
    class StaticFileReader : public IFileReader
    {
    public:
        
        StaticFileReader();

    
        StaticFileReader(std::string & file_path);
        StaticFileReader(StaticFileReader & other) = delete;
        StaticFileReader(StaticFileReader && other);
        
        StaticFileReader & operator=(StaticFileReader & other) = delete;
        StaticFileReader & operator=(StaticFileReader && other);
        
        
        ~StaticFileReader();

        bool open()override;
        bool open(const std::string  & file_path) override;
        bool close() override;
        void  reload() override;

        ByteArray read(size_t size) override;
        ByteArray readAll() override;
        
        
        bool is_open() const override;
        bool empty() const override;
        bool endread() override;
        
        
        size_t size() const override;                 
        std::string  path() const override;
    private:
        
        void move(StaticFileReader && other);
        std::string file_path;
        std::unique_ptr<std::ifstream> stream;
        size_t size_ {0}; 
        size_t pos {0};
    };

}

#endif